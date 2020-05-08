/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <chrono>
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <egt/ui>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace egt;

class Bubble : public ImageLabel
{
public:
    Bubble(int xspeed, int yspeed, const Point& point) noexcept
        : ImageLabel(Image("file:smallbubble.png"), "", Rect(point, Size())),
          m_xspeed(xspeed),
          m_yspeed(yspeed)
    {
        flags().set(Widget::Flag::no_layout);
    }

    Bubble(const Bubble&) = default;
    Bubble(Bubble&&) = default;
    Bubble& operator=(const Bubble&) = default;
    Bubble& operator=(Bubble&&) = default;
    virtual ~Bubble() = default;

    bool animate()
    {
        bool visible = Rect(Point(0, 0), Application::instance().screen()->size()).intersect(box());

        if (visible)
        {
            Point to(box().point());
            to += Point(m_xspeed, m_yspeed);
            move(to);
        }

        return visible;
    }

private:

    Bubble() = delete;

    int m_xspeed;
    int m_yspeed;
};

class MainWindow : public TopWindow
{
public:
    MainWindow()
        : TopWindow(Size()),
          e1(r())
    {
        background(Image("file:water.png"));

        m_label = make_shared<Label>("Objects: 0",
                                     Rect(Point(10, 10),
                                          Size(150, 40)),
                                     AlignFlag::left | AlignFlag::center_horizontal | AlignFlag::center_vertical);
        m_label->color(Palette::ColorId::text, Palette::white);
        m_label->color(Palette::ColorId::bg, Palette::transparent);
        add(top(left(m_label)));

        m_sprite = make_shared<Sprite>(Image("file:diver.png"), Size(390, 312), 16, Point(0, 0));
        m_sprite->no_layout(true);
        add(m_sprite);
        m_sprite->show();
    }

    void handle(Event& event) override
    {
        TopWindow::handle(event);

        switch (event.id())
        {
        case EventId::raw_pointer_move:
            spawn(display_to_local(event.pointer().point));
            break;
        default:
            break;
        }
    }

    void spawn(const Point& p)
    {
        auto xspeed = 0;
        auto yspeed = speed_dist(e1);
        auto offset = offdist(e1);
        auto size = size_dist(e1);

        // has to move at some speed
        if (yspeed == 0)
            yspeed = 1;

        m_images.emplace_back(make_shared<Bubble>(xspeed, yspeed, p));
        auto& image = m_images.back();
        add(image);
        image->image_align(AlignFlag::expand_horizontal | AlignFlag::expand_vertical);
        image->resize_by_ratio(size);
        image->move(Point(p.x() - image->box().width() / 2 + offset,
                          p.y() - image->box().height() / 2 + offset));
        objects_changed();
    }

    void animate()
    {
        for (auto x = m_images.begin(); x != m_images.end();)
        {
            auto& image = *x;
            if (!image->animate())
            {
                image->detach();
                x = m_images.erase(x);
                objects_changed();
            }
            else
            {
                x++;
            }
        }
    }

    void objects_changed()
    {
        ostringstream ss;
        ss << "Objects: " << m_images.size();
        m_label->text(ss.str());
    }

    vector<shared_ptr<Bubble>> m_images;
    shared_ptr<Label> m_label;
    shared_ptr<Sprite> m_sprite;

    std::random_device r;
    std::default_random_engine e1;
    std::uniform_int_distribution<int> speed_dist{-20, -1};
    std::uniform_int_distribution<int> offdist{-20, 20};
    std::uniform_int_distribution<int> size_dist{10, 100};
};

int main(int argc, char** argv)
{
    Application app(argc, argv, "water");
#ifdef EXAMPLEDATA
    add_search_path(EXAMPLEDATA);
#endif
    MainWindow win;

    vector<Sprite*> sprites;

#define SPRITE1
#ifdef SPRITE1
    Sprite sprite1(Image("file:fish.png"), Size(252, 209), 8, Point(0, 0));
    sprite1.no_layout(true);
    win.add(sprite1);
    sprite1.show();
    sprites.push_back(&sprite1);
#endif

#define SPRITE2
#ifdef SPRITE2
    Sprite sprite2(Image("file:fish2.png"), Size(100, 87), 6, Point(0, 0));
    sprite2.no_layout(true);
    win.add(sprite2);
    sprite2.show();
    sprites.push_back(&sprite2);
#endif

    sprites.push_back(win.m_sprite.get());

    PeriodicTimer animatetimer(std::chrono::milliseconds(30));
    animatetimer.on_timeout([&win]()
    {
        win.animate();
    });
    animatetimer.start();

    PeriodicTimer animatetimer2(std::chrono::milliseconds(100));
    animatetimer2.on_timeout([&sprites]()
    {
        for (auto& sprite : sprites)
            sprite->advance();
    });
    animatetimer2.start();

    PeriodicTimer spawntimer(std::chrono::seconds(1));
    spawntimer.on_timeout([&win]()
    {
        if (win.m_images.size() > 30)
            return;

        static std::uniform_int_distribution<int> xoffdist(-win.width() / 2, win.width() / 2);
        int offset = xoffdist(win.e1);

        static std::uniform_int_distribution<int> count_dist(1, 10);
        int count = count_dist(win.e1);

        Point p(win.box().center());
        p.y(win.box().height());
        p.x(p.x() + offset);

        while (count--)
            win.spawn(p);
    });
    spawntimer.start();

#ifdef SPRITE1
    PropertyAnimator a1(-sprite1.size().width(), Application::instance().screen()->size().width(),
                        std::chrono::milliseconds(10000),
                        easing_linear);
    a1.on_change([&sprite1](PropertyAnimator::Value value){
            sprite1.x(value);
        });
    a1.start();

    PeriodicTimer floattimer(std::chrono::milliseconds(1000 * 12));
    floattimer.on_timeout([&a1, &sprite1, &win]()
    {

        static std::uniform_int_distribution<int> yoffdist(0, win.height() - sprite1.size().height());
        int y = yoffdist(win.e1);

        sprite1.move(Point(-sprite1.size().width(), y));
        a1.start();
    });
    floattimer.start();
#endif

#ifdef SPRITE2
    PropertyAnimator a2(-sprite2.size().width(), Application::instance().screen()->size().width(),
                        std::chrono::milliseconds(12000),
                        easing_linear);
    a2.on_change([&sprite2](PropertyAnimator::Value value){
            sprite2.x(value);
        });
    a2.start();

    PeriodicTimer floattimer2(std::chrono::milliseconds(1000 * 15));
    floattimer2.on_timeout([&a2, &sprite2, &win]()
    {
        static std::uniform_int_distribution<int> yoffdist(0, win.height() - sprite2.size().height());
        int y = yoffdist(win.e1);

        sprite2.move(Point(-sprite2.size().width(), y));
        a2.start();
    });
    floattimer2.start();
#endif

    Label label1("CPU: ----");
    label1.color(Palette::ColorId::text, Palette::white);
    label1.color(Palette::ColorId::bg, Palette::transparent);
    win.add(bottom(left(label1)));

    egt::experimental::CPUMonitorUsage tools;
    PeriodicTimer cputimer(std::chrono::seconds(1));
    cputimer.on_timeout([&label1, &tools]()
    {
        tools.update();
        ostringstream ss;
        ss << "CPU: " << static_cast<int>(tools.usage()) << "%";
        label1.text(ss.str());
    });
    cputimer.start();

    win.show();

    return app.run();
}
