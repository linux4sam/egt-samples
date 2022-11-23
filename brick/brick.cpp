/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <egt/ui>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

using namespace std;
using namespace egt;

class GameWindow : public TopWindow
{
public:
    static const int ROWS;

    GameWindow()
        : m_grid1(Rect(Point(0, 50), Size(width(), 80)),
                  StaticGrid::GridSize(width() / 100, ROWS)),
          m_grid2(Rect(Point(0, 50 + 80 + 30), Size(width(), 80)),
                  StaticGrid::GridSize(width() / 100, ROWS)),
          m_ball(Image("file:small_ball.png")),
          m_paddle(Image("file:paddle.png")),
          m_label("-", AlignFlag::left | AlignFlag::center_vertical),
          e1(random())
    {
        background(Image("file:brick_background.png"));

        add(m_grid1);
        add(m_grid2);
        m_grid1.margin(5);
        m_grid1.horizontal_space(5);
        m_grid1.vertical_space(5);
        m_grid1.color(Palette::ColorId::border, Palette::transparent);
        m_grid2.margin(5);
        m_grid2.horizontal_space(5);
        m_grid2.vertical_space(5);
        m_grid2.color(Palette::ColorId::border, Palette::transparent);

        for (int c = 0; c < width() / 100; c++)
        {
            for (int r = 0; r < ROWS; r++)
            {
                ostringstream ss;
                ss << "file:brick" << r << ".png";
                auto block = make_shared<ImageLabel>(Image(ss.str()));
                m_blocks.push_back(block);
                m_grid1.add(expand(block), c, r);
            }
        }

        for (int c = 0; c < width() / 100; c++)
        {
            for (int r = 0; r < ROWS; r++)
            {
                ostringstream ss;
                ss << "file:brick" << r + 2 << ".png";
                auto block = make_shared<ImageLabel>(Image(ss.str()));
                m_blocks.push_back(block);
                m_grid2.add(expand(block), c, r);
            }
        }

        add(m_paddle);

        m_ball.autoresize(false);
        m_ball.resize(Size(Ratio<int>(width(), 5), Ratio<int>(width(), 5)));
        m_ball.image_align(AlignFlag::expand_horizontal | AlignFlag::expand_vertical);
        add(m_ball);

        m_label.color(Palette::ColorId::label_text, Palette::white);
        add(top(left(m_label)));

        reset_game();
    }

    // TODO: convert this to use POINTER_DRAG events
    void handle(Event& event) override
    {
        Window::handle(event);

        switch (event.id())
        {
        case EventId::keyboard_repeat:
        case EventId::keyboard_down:
        {
            if (event.key().keycode == EKEY_LEFT || event.key().keycode == EKEY_RIGHT)
            {
                int x;
                m_running = true;
                if (event.key().keycode == EKEY_LEFT)
                    x = m_paddle.x() - (event.id() == EventId::keyboard_repeat ? 15 : 10);
                else
                    x = m_paddle.x() + (event.id() == EventId::keyboard_repeat ? 15 : 10);

                if (x > -m_paddle.width() && x < width())
                    m_paddle.move(Point(x, m_paddle.y()));

                event.stop();
            }
            else if (event.key().keycode == EKEY_UP)
            {
                m_xspeed *= 1.5;
                m_yspeed *= 1.5;
                event.stop();
            }
            else if (event.key().keycode == EKEY_DOWN)
            {
                m_xspeed *= .5;
                m_yspeed *= .5;
                event.stop();
            }
            break;
        }
        case EventId::raw_pointer_down:
            m_running = true;
            break;
        case EventId::raw_pointer_move:
            m_paddle.move(Point(event.pointer().point.x() - m_paddle.width() / 2, m_paddle.y()));
            event.stop();
            break;
        default:
            break;
        }
    }

    void reset_game()
    {
        for (auto block : m_blocks)
            block->show();

        m_ball.move(Point(width() / 2 - m_ball.width() / 2, height() - m_paddle.height() - 25 - m_ball.height() - 100));
        m_paddle.move(Point(width() / 2 - m_paddle.width() / 2, height() - m_paddle.height() - 25));

        std::uniform_real_distribution<float> speed_dist(2.0, 5.0);
        m_xspeed = speed_dist(e1);
        m_yspeed = speed_dist(e1);
        m_points = 0;

        ostringstream ss;
        ss << "Points: " << m_points;
        m_label.text(ss.str());

        m_running = false;
    }

    void add_points(int points)
    {
        m_points += points;

        ostringstream ss;
        ss << "Points: " << m_points;
        m_label.text(ss.str());
    }

    void animate()
    {
        if (!m_running)
            return;

        // advance ball
        Point to(m_ball.box().point());
        to += Point(m_xspeed, m_yspeed);
        m_ball.move(to);

        // hit block
        for (auto block : m_blocks)
        {
            if (!block->visible())
                continue;

            if (block->to_parent(block->box()).intersect(m_ball.box()))
            {
                block->hide();
                m_yspeed *= -1.0;
                add_points(1);
                break;
            }
        }

        // hit paddle
        if (m_paddle.box().intersect(m_ball.box()))
        {
            m_yspeed *= -1.0;
        }

        // bounce off walls
        if (m_ball.x() + m_ball.width() > width() || m_ball.x() < 0)
        {
            m_xspeed *= -1.0;
        }

        // below paddle
        if (m_ball.y() + m_ball.height() > height())
        {
            reset_game();
        }

        // win
        if (m_ball.y() < 0)
        {
            reset_game();
        }
    }

private:

    StaticGrid m_grid1;
    StaticGrid m_grid2;
    ImageLabel m_ball;
    ImageLabel m_paddle;
    float m_xspeed;
    float m_yspeed;
    vector<shared_ptr<ImageLabel>> m_blocks;
    Label m_label;
    unsigned int m_points;
    bool m_running{false};
    std::random_device random;
    std::default_random_engine e1;
};

const int GameWindow::ROWS = 2;

int main(int argc, char** argv)
{
    Application app(argc, argv, "brick");

    GameWindow win;

    PeriodicTimer animatetimer(std::chrono::milliseconds(30));
    animatetimer.on_timeout([&win]()
    {
        win.animate();
    });
    animatetimer.start();

    win.show();

    return app.run();
}
