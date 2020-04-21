/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <egt/ui>
#include <egt/detail/filesystem.h>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;
using namespace egt;

int main(int argc, char** argv)
{
    std::string dir;
    if (argc >= 2)
        dir = argv[1];
    else
    {
        cerr << argv[0] << " DIRECTORY" << endl;
        return 1;
    }

    Application app(argc, argv, "icon");

    TopWindow win;

    auto NAV_WIDTH = 50;

    ImageButton left(win, Image("icon:arrow_left.png;32"), "", Rect(0, 0, NAV_WIDTH, win.height()));
    left.min_size_hint(Size(1,1));
    left.resize(Size(NAV_WIDTH, win.height()));
    left.align(AlignFlag::left);

    ImageButton right(win, Image("icon:arrow_right.png;32"), "", Rect(0, 0, NAV_WIDTH, win.height()));
    right.min_size_hint(Size(1,1));
    right.resize(Size(NAV_WIDTH, win.height()));
    right.align(AlignFlag::right);

    ScrolledView view0(Rect(NAV_WIDTH, 0, win.width() - (NAV_WIDTH * 2), win.height()));
    win.add(view0);

    PropertyAnimator swipe(0, 0, std::chrono::milliseconds(1000), easing_quintic_easein);
    swipe.on_change(std::bind(&ScrolledView::hoffset, std::ref(view0), std::placeholders::_1));

    right.on_event([&](Event&)
    {
        swipe.starting(view0.offset().x());
        swipe.ending(view0.offset().x() - view0.width());
        swipe.start();
    }, {EventId::pointer_click});

    left.on_event([&](Event&)
    {
        swipe.starting(view0.offset().x());
        swipe.ending(view0.offset().x() + view0.width());
        swipe.start();
    }, {EventId::pointer_click});

    std::vector<std::string> files = detail::glob(dir + "/" + "*.png");

    StaticGrid grid0(Rect(0, 0, files.size() / 6 * 160, win.height()),
                     StaticGrid::GridSize(files.size() / 6, 6));
    view0.add(grid0);

    for (auto& file : files)
    {
        std::string basename = file.substr(file.find_last_of("/\\") + 1);
        basename = detail::replace_all(basename, ".png", "");
        auto icon = make_shared<ImageLabel>(Image("file:" + file), basename);
        grid0.add(expand(icon));
        icon->image_align(egt::AlignFlag::top);
        icon->text_align(egt::AlignFlag::center);
    }

    win.show();

    return app.run();
}
