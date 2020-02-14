/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <cmath>
#include <cstdio>
#include <egt/detail/filesystem.h>
#include <egt/ui>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;
using namespace egt;

int main(int argc, char** argv)
{
    Application app(argc, argv, "gallery");

    std::vector<std::string> files = detail::glob(resolve_file_path("movies/") + "*trailer*.jpg");

    TopWindow win;
    win.name("win");
    win.color(Palette::ColorId::bg, Palette::black);

    VideoWindow player(Size(320, 192));
    player.volume(50);

    auto fullscale = static_cast<double>(Application::instance().screen()->size().width()) /
                     static_cast<double>(player.width());
    if (fullscale <= 0)
        fullscale = 1.0;

    ImageLabel logo(Image("icon:microchip_logo_white.png;128"));
    win.add(logo);
    logo.align(AlignFlag::left | AlignFlag::top);
    logo.margin(10);

    auto grid_height = (win.size().height() - logo.height()) / 2;

    ScrolledView view0(Rect(0, logo.height(), win.size().width(), grid_height));
    view0.color(Palette::ColorId::bg, Palette::black);
    view0.name("view0");
    win.add(view0);

    StaticGrid grid0(Rect(0, 0, files.size() * 150, grid_height), std::make_tuple(files.size(), 1));
    grid0.name("grid0");
    view0.add(grid0);

    PropertyAnimatorType<float> animator(1.0, fullscale, std::chrono::milliseconds(800));
    bool videoshown = false;

    for (auto& file : files)
    {
        auto l = make_shared<ImageButton>(Image("file:" + file));
        l->fill_flags().clear();
        l->flags().clear(Widget::Flag::grab_mouse);
        l->on_click([&player, file, &animator, &videoshown](Event&)
        {
            cout << "playing " << file << ".avi" << endl;
            player.media(file + ".avi");
            player.play();
            player.show();
            videoshown = true;

            animator.clear_change_callbacks();
            animator.on_change([&player](PropertyAnimatorType<float>::Value value){
                    player.scale(value);
                });
            animator.start();
        });

        l->align(AlignFlag::center);
        grid0.add(l);
    }

    ScrolledView view1(Rect(0, logo.height() + grid_height + 1, win.size().width(), grid_height));
    view1.color(Palette::ColorId::bg, Palette::black);
    view1.name("view1");
    win.add(view1);

    StaticGrid grid1(Rect(0, 0, files.size() * 150, grid_height), std::make_tuple(files.size(), 1));
    grid1.name("grid1");
    view1.add(grid1);

    for (auto& file : files)
    {
        auto l = make_shared<ImageButton>(Image("file:" + file));
        l->fill_flags().clear();
        l->flags().clear(Widget::Flag::grab_mouse);
        l->on_click([&player, file, &animator, &videoshown](Event&)
        {
            cout << "playing " << file << ".avi" << endl;
            player.media(file + ".avi");
            player.play();
            player.show();
            videoshown = true;

            animator.clear_change_callbacks();
            animator.on_change([&player](PropertyAnimatorType<float>::Value value){
                    player.scale(value);
                });
            animator.start();
        });

        l->align(AlignFlag::center);
        grid1.add(l);
    }

    Popup popup(Size(Application::instance().screen()->size().width() / 2,
                     Application::instance().screen()->size().height() / 2));
    popup.name("popup");
    Button button("Hello World");
    popup.add(button);
    button.align(AlignFlag::center);
    button.name("hw");

    ImageButton settings(Image("file:settings.png"), "", Rect());
    win.add(settings);
    settings.fill_flags().clear();
    settings.align(AlignFlag::right | AlignFlag::top);
    settings.margin(10);
    settings.on_click([&popup](Event&)
    {
        if (popup.visible())
            popup.hide();
        else
            popup.show_centered();
        return 1;
    });
    win.add(popup);

    win.add(player);

    win.show();

    Input::global_input().on_event([&player, &videoshown](Event & event)
    {
        if (videoshown)
        {
            player.pause();
            player.hide();
            videoshown = false;
            event.stop();
        }
    }, {EventId::pointer_click});

    return app.run();
}
