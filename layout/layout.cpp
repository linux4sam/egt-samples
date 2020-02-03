/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <egt/detail/serialize.h>
#include <egt/form.h>
#include <egt/shapes.h>
#include <egt/themes/midnight.h>
#include <egt/themes/shamrock.h>
#include <egt/themes/sky.h>
#include <egt/ui>
#include <egt/uiloader.h>
#include <memory>

using namespace egt;
using namespace egt::experimental;
using namespace egt::detail;
using namespace std;

using create_function = std::function<shared_ptr<Widget>()>;

template <class T>
shared_ptr<Widget> create_widget()
{
    auto instance = make_shared<T>();
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<Button>()
{
    auto instance = make_shared<Button>("Button");
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<Label>()
{
    auto instance = make_shared<Label>("Label");
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<CheckBox>()
{
    auto instance = make_shared<CheckBox>("CheckBox");
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<TextBox>()
{
    auto instance = make_shared<TextBox>("Text");
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<RadioBox>()
{
    auto instance = make_shared<RadioBox>("RadioBox");
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<ComboBox>()
{
    ComboBox::ItemArray combo_items;
    for (auto x = 0; x < 5; x++)
        combo_items.push_back("item " + std::to_string(x));

    auto instance = make_shared<ComboBox>(combo_items);
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<ListBox>()
{
    auto instance = make_shared<ListBox>();

    for (auto x = 0; x < 5; x++)
        instance->add_item(std::make_shared<StringItem>("item " + std::to_string(x)));

    instance->resize(Size(100, 200));

    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<ImageLabel>()
{
    auto instance = make_shared<ImageLabel>(Image("file:icons/image_default.png"));
    instance->image_align(AlignFlag::expand_horizontal | AlignFlag::expand_vertical);
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<ScrolledView>()
{
    auto instance = make_shared<ScrolledView>();
    instance->resize(Size(200, 200));
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<StaticGrid>()
{
    auto instance = make_shared<StaticGrid>(std::make_tuple(2, 2), 1);
    instance->resize(Size(200, 200));
    instance->border(instance->theme().default_border());
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<SelectableGrid>()
{
    auto instance = make_shared<SelectableGrid>(std::make_tuple(2, 2), 1);
    instance->resize(Size(200, 200));
    instance->border(instance->theme().default_border());
    return static_pointer_cast<Widget>(instance);
}

template <>
shared_ptr<Widget> create_widget<Slider>()
{
    auto instance = make_shared<Slider>();
    instance->value(10);
    return static_pointer_cast<Widget>(instance);
}

#ifdef EGT_HAS_CHART
template <>
shared_ptr<Widget> create_widget<PieChart>()
{
    auto instance = make_shared<PieChart>();

    PieChart::DataArray data;
    data.push_back(make_pair(.25, "truck"));
    data.push_back(make_pair(.55, "car"));
    data.push_back(make_pair(.10, "bike"));
    data.push_back(make_pair(.05, "motorcycle"));
    data.push_back(make_pair(.05, "plane"));
    instance->data(data);

    return static_pointer_cast<Widget>(instance);
}
#endif

struct widget_types
{
    std::string name;
    std::string icon;
    create_function create;
};

static vector<widget_types> widgets =
{
    { "frame", "file:icons/frame.png", create_widget<Frame> },
    { "vsizer", "file:icons/vertical.png", create_widget<VerticalBoxSizer> },
    { "hsizer", "file:icons/horizontal.png", create_widget<HorizontalBoxSizer> },
    { "flexsizer", "file:icons/flex.png", create_widget<FlexBoxSizer> },
    { "grid", "file:icons/grid.png", create_widget<StaticGrid>},
    { "grid", "file:icons/selectgrid.png", create_widget<SelectableGrid>},
    { "view", "file:icons/view.png", create_widget<ScrolledView>},
    { "circle", "file:icons/circle.png", create_widget<CircleWidget>},
    { "line", "file:icons/line.png", create_widget<LineWidget>},
    { "square", "file:icons/square.png", create_widget<RectangleWidget>},
    { "buttton", "file:icons/button.png", create_widget<Button> },
    { "label", "file:icons/label.png", create_widget<Label> },
    { "textbox", "file:icons/textbox.png", create_widget<TextBox>},
    { "listbox", "file:icons/listbox.png", create_widget<ListBox>},
    { "imagelabel", "file:icons/imagelabel.png", create_widget<ImageLabel>},
    { "radiobox", "file:icons/radiobox.png", create_widget<RadioBox>},
    { "combobox", "file:icons/combobox.png", create_widget<ComboBox>},
    { "checkbox", "file:icons/checkbox.png", create_widget<CheckBox>},
    { "togglebox", "file:icons/togglebox.png", create_widget<ToggleBox>},
    { "slider", "file:icons/slider.png", create_widget<Slider>},
    { "progressbar", "file:icons/progress.png", create_widget<ProgressBar>},
    { "spinprogress", "file:icons/spinprogress.png", create_widget<SpinProgress>},
    { "levelmeter", "file:icons/levelmeter.png", create_widget<LevelMeter>},
    { "analogmeter", "file:icons/analogmeter.png", create_widget<AnalogMeter>},
#ifdef EGT_HAS_CHART
    { "linechart", "file:icons/linechart.png", create_widget<LineChart>},
    { "piechart", "file:icons/piechart.png", create_widget<PieChart>},
#endif
    { "radial", "file:icons/radial.png", create_widget<RadialType<int>>},
};

template<class T>
shared_ptr<Widget> create_option(std::function<void(T)> set,
                                 std::function<T()> get)
{
    auto x = make_shared<TextBox>(std::to_string(get()));
    x->on_text_changed([x, set]()
    {
        if (!x->text().empty())
            set(std::stoi(x->text()));
    });
    return static_pointer_cast<Widget>(x);
}

template<>
shared_ptr<Widget> create_option(std::function<void(string)> set,
                                 std::function<string()> get)
{
    auto x = make_shared<TextBox>(get());
    x->on_text_changed([x, set]()
    {
        if (!x->text().empty())
            set(x->text());
    });
    return static_pointer_cast<Widget>(x);
}

class MainWindow : public TopWindow
{
public:

    MainWindow()
    {
        auto vsizer = make_shared<BoxSizer>(Orientation::vertical);
        add(expand(vsizer));

        auto frame = make_shared<Frame>(Size(0, 60));
        vsizer->add(expand_horizontal(frame));

        auto logo = make_shared<ImageLabel>(Image("icon:egt_logo_black.png"));
        logo->margin(1);
        logo->align(AlignFlag::center_horizontal | AlignFlag::center_vertical);
        frame->add(logo);

        ComboBox::ItemArray combo_items =
        {
            "Default",
            "Midnight",
            "Sky",
            "Shamrock"
        };
        auto combo = make_shared<ComboBox>(combo_items);
        combo->align(AlignFlag::center_vertical | AlignFlag::right);
        combo->margin(5);
        frame->add(combo);

        combo->on_selected_changed([combo, this]()
        {
            auto s = combo->item_at(combo->selected());

            if (s == "Default")
                global_theme(detail::make_unique<Theme>());
            else if (s == "Midnight")
                global_theme(detail::make_unique<MidnightTheme>());
            else if (s == "Sky")
                global_theme(detail::make_unique<SkyTheme>());
            else if (s == "Shamrock")
                global_theme(detail::make_unique<ShamrockTheme>());

            this->damage();
        });

        m_hsizer = make_shared<BoxSizer>(Orientation::horizontal);
        vsizer->add(expand(m_hsizer));

        m_grid = make_shared<SelectableGrid>(std::make_tuple(3, 10), 5);
        m_grid->horizontal_ratio(15);
        m_grid->resize(Size(200, 0));
        m_hsizer->add(expand_vertical(m_grid));

        for (auto& w : widgets)
        {
            auto btn = make_shared<ImageButton>(Image(w.icon));
            btn->fill_flags().clear();
            m_grid->add(egt::center(btn));
        }

        m_canvas = make_shared<Window>();
        m_canvas->border(global_theme().default_border());
        m_canvas->fill_flags(Theme::FillFlag::blend);
        m_canvas->align(AlignFlag::expand_horizontal | AlignFlag::expand_vertical);
        m_canvas->horizontal_ratio(80);
        m_canvas->show();
        m_hsizer->add(m_canvas);

        m_canvas->special_child_draw_callback([](Painter & painter, Widget * widget)
        {
            Painter::AutoSaveRestore sr3(painter);
            auto cr = painter.context().get();
            auto b = widget->box();
            b += Point(2 / 2., 2 / 2.);
            b -= Size(2, 2);
            painter.draw(b);
            painter.set(Palette::blue);
            static const double dashed[] = {1.0};
            cairo_set_dash(cr, dashed, 1, 0);
            painter.line_width(2);
            cairo_stroke(cr);
        });

        m_form = make_shared<Form>("Properties");
        m_form->resize(Size(250, 0));
        m_form->align(AlignFlag::expand_vertical);
        // todo: not working
        //m_form->horizontal_ratio(100);
        m_hsizer->add(m_form);

        Input::global_input().on_event([this](Event & event)
        {
            switch (event.key().keycode)
            {
            case EKEY_DELETE:
                if (m_selected)
                {
                    m_selected->detach();
                    m_selected = nullptr;
                    m_form->remove_options();
                }
                break;
            default:
                break;
            }
        }, {EventId::keyboard_down});

        auto save = make_shared<Button>("Save");
        save->align(AlignFlag::center_vertical | AlignFlag::left);
        save->margin(5);
        frame->add(save);

        save->on_click([this](Event&){
                XmlWidgetSerializer xml;
                m_canvas->walk([&xml](Widget* widget, int level){
                        xml.add(widget, level);
                        return true;
                    });
                xml.write("ui.xml");
                xml.write(cout);
            });
    }

    void handle(Event& event) override
    {
        TopWindow::handle(event);

        switch (event.id())
        {
        case EventId::pointer_click:
        {
            if (event.pointer().btn == Pointer::Button::right)
            {
                Point pos = display_to_local(event.pointer().point);
                if (m_canvas->box().intersect(pos))
                {
                    auto parent = static_cast<Frame*>(m_canvas->hit_test(event.pointer().point));
                    if (parent && !parent->flags().is_set(Widget::Flag::frame))
                        parent = nullptr;
                    auto p = m_grid->selected();
                    auto index = p.x() + 3 * p.y();
                    auto widget = widgets[index].create();
                    add_widget(widget, event.pointer().point, parent);
                    event.stop();
                }
            }
            break;
        }
        default:
            break;
        }
    }

    template<class T>
    void show_properties(T* widget)
    {
        m_form->remove_options();

        m_form->add_group("Widget");
        m_form->add_option("Name",
                           create_option<string>([widget](const std::string& v) { widget->name(v); },
                                                 [widget]() { return widget->name(); }));
        m_form->add_option("X",
                           create_option<int>([widget](int v) { widget->x(v); },
                                              [widget]() { return widget->x(); }));
        m_form->add_option("Y",
                           create_option<int>([widget](int v) { widget->y(v); },
                                              [widget]() { return widget->y(); }));
        m_form->add_option("Width",
                           create_option<int>([widget](int v) { widget->width(v); },
                                              [widget]() { return widget->width(); }));
        m_form->add_option("Height",
                           create_option<int>([widget](int v) { widget->height(v); },
                                              [widget]() { return widget->height(); }));
        m_form->add_option("Border",
                           create_option<int>([widget](int v) { widget->border(v); },
                                              [widget]() { return widget->border(); }));
        m_form->add_option("Margin",
                           create_option<int>([widget](int v) { widget->margin(v); },
                                              [widget]() { return widget->margin(); }));
        m_form->add_option("Padding",
                           create_option<int>([widget](int v) { widget->padding(v); },
                                              [widget]() { return widget->padding(); }));
        m_form->add_option("X Ratio",
                           create_option<int>([widget](int v) { widget->xratio(v); },
                                              [widget]() { return widget->xratio(); }));
        m_form->add_option("Y Ratio",
                           create_option<int>([widget](int v) { widget->yratio(v); },
                                              [widget]() { return widget->yratio(); }));
        m_form->add_option("H Ratio",
                           create_option<int>([widget](int v) { widget->horizontal_ratio(v); },
                                              [widget]() { return widget->horizontal_ratio(); }));
        m_form->add_option("V Ratio",
                           create_option<int>([widget](int v) { widget->vertical_ratio(v); },
                                              [widget]() { return widget->vertical_ratio(); }));

        auto centerh = make_shared<CheckBox>("center horizontal");
        if (widget->align().is_set(AlignFlag::center_horizontal))
            centerh->checked(true);
        centerh->on_checked_changed([widget, centerh]()
        {
            if (centerh->checked())
                widget->align(widget->align() | AlignFlag::center_horizontal);
            else
                widget->align().clear(AlignFlag::center_horizontal);
        });
        m_form->add_option(centerh);

        auto centerv = make_shared<CheckBox>("center vertical");
        if (widget->align().is_set(AlignFlag::center_vertical))
            centerv->checked(true);
        centerv->on_checked_changed([widget, centerv]()
        {
            if (centerv->checked())
                widget->align(widget->align() | AlignFlag::center_vertical);
            else
                widget->align().clear(AlignFlag::center_vertical);
        });
        m_form->add_option(centerv);

        auto left = make_shared<CheckBox>("left");
        if (widget->align().is_set(AlignFlag::left))
            left->checked(true);
        left->on_checked_changed([widget, left]()
        {
            if (left->checked())
                widget->align(widget->align() | AlignFlag::left);
            else
                widget->align().clear(AlignFlag::left);
        });
        m_form->add_option(left);

        auto right = make_shared<CheckBox>("right");
        if (widget->align().is_set(AlignFlag::right))
            right->checked(true);
        right->on_checked_changed([widget, right]()
        {
            if (right->checked())
                widget->align(widget->align() | AlignFlag::right);
            else
                widget->align().clear(AlignFlag::right);
        });
        m_form->add_option(right);

        auto top = make_shared<CheckBox>("top");
        if (widget->align().is_set(AlignFlag::top))
            top->checked(true);
        top->on_checked_changed([widget, top]()
        {
            if (top->checked())
                widget->align(widget->align() | AlignFlag::top);
            else
                widget->align().clear(AlignFlag::top);
        });
        m_form->add_option(top);

        auto bottom = make_shared<CheckBox>("bottom");
        if (widget->align().is_set(AlignFlag::bottom))
            bottom->checked(true);
        bottom->on_checked_changed([widget, bottom]()
        {
            if (bottom->checked())
                widget->align(widget->align() | AlignFlag::bottom);
            else
                widget->align().clear(AlignFlag::bottom);
        });
        m_form->add_option(bottom);

        auto expand_horizontal = make_shared<CheckBox>("expand horizontal");
        if (widget->align().is_set(AlignFlag::expand_horizontal))
            expand_horizontal->checked(true);
        expand_horizontal->on_checked_changed([widget, expand_horizontal]()
        {
            if (expand_horizontal->checked())
                widget->align(widget->align() | AlignFlag::expand_horizontal);
            else
                widget->align().clear(AlignFlag::expand_horizontal);
        });
        m_form->add_option(expand_horizontal);

        auto expand_vertical = make_shared<CheckBox>("expand vertical");
        if (widget->align().is_set(AlignFlag::expand_vertical))
            expand_vertical->checked(true);
        expand_vertical->on_checked_changed([widget, expand_vertical]()
        {
            if (expand_vertical->checked())
                widget->align(widget->align() | AlignFlag::expand_vertical);
            else
                widget->align().clear(AlignFlag::expand_vertical);
        });
        m_form->add_option(expand_vertical);
    }

    void add_widget(const shared_ptr<Widget>& widget, const DisplayPoint& point, Frame* parent)
    {
        if (!parent)
            return;

        cout << "Adding widget at " << point << " to " << parent->name() << endl;

        parent->add(widget);
        widget->move(parent->display_to_local(point));

        if (widget->size().empty())
            widget->resize(widget->min_size_hint());

        if (widget->size().empty())
            widget->resize(Size(100, 100));

        widget->walk([this](Widget* widget, int level){
                widget->clear_handlers();
                widget->on_event([this, widget](Event & event)
                                 {
                                     static Point start_point;

                                     /// @todo drag is broken if you drag an item over one it is under

                                     switch (event.id())
                                     {
                                     case EventId::raw_pointer_down:
                                         if (event.pointer().btn == Pointer::Button::left)
                                         {
                                             show_properties(widget);
                                             m_selected = widget;
                                         }
                                         break;
                                     case EventId::pointer_drag_start:
                                         widget->align().clear();
                                         start_point = widget->box().point();
                                         event.stop();
                                         break;
                                     case EventId::pointer_drag:
                                     {
                                         auto diff = event.pointer().drag_start - event.pointer().point;
                                         widget->move(start_point - Point(diff.x(), diff.y()));
                                         break;
                                     }
                                     case EventId::pointer_drag_stop:
                                         show_properties(widget);
                                         m_selected = widget;
                                         break;
                                     default:
                                         break;
                                     }
                                 });

                return true;
            });

        m_selected = widget.get();
        show_properties(widget.get());
    }

    void load(const std::string& file)
    {
        egt::experimental::UiLoader loader;
        auto canvas = dynamic_pointer_cast<Window>(loader.load(file));

        if (canvas)
        {
            m_canvas->remove_all();

            while (canvas->count_children())
            {
                auto child = canvas->child_at(0);
                child->detach();
                add_widget(child, m_canvas->local_to_display(child->point()), m_canvas.get());
            }

            m_canvas->layout();
        }
        else
        {
            cerr << "no window loaded" << endl;
        }
    }

private:

    shared_ptr<Window> m_canvas;
    shared_ptr<Form> m_form;
    shared_ptr<SelectableGrid> m_grid;
    shared_ptr<BoxSizer> m_hsizer;
    Widget* m_selected{nullptr};
};

int main(int argc, const char** argv)
{
    Application app(argc, argv, "layout");

    MainWindow win;
    win.show();

    if (argc >= 2)
        win.load(argv[1]);

#if 0
    OstreamWidgetSerializer s(cout);
    win.walk(std::bind(&OstreamWidgetSerializer::add, std::ref(s),
                       std::placeholders::_1, std::placeholders::_2));

    XmlWidgetSerializer xml;
    win.walk(std::bind(&XmlWidgetSerializer::add, std::ref(xml),
                       std::placeholders::_1, std::placeholders::_2));
    xml.write("ui.xml");
    xml.write(cout);
#endif

    return app.run();
}
