/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <ctime>
#include <egt/detail/filesystem.h>
#include <egt/detail/imagecache.h>
#include <egt/network/http.h>
#include <egt/ui>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <sstream>
#include <string>

using namespace std;
using namespace egt;
using namespace egt::experimental;
using namespace egt::detail;

using download_callback = std::function<void(const HttpClientRequest::buffer_type& data)>;

static void download(const std::string& url, download_callback callback, bool allow_cached = true)
{
    cout << "request " << url << endl;

    auto filename = detail::extract_filename(url);

    if (allow_cached)
    {
        if (!filename.empty() && detail::exists(filename))
        {
            callback(detail::read_file(filename));
            return;
        }
    }

    // TODO: memory leak
    auto session = new HttpClientRequest(url);
    session->start([filename, callback](const std::string & url, HttpClientRequest::buffer_type && html)
    {
        if (!filename.empty())
        {
            std::ofstream out(filename, std::ofstream::binary |
                              std::ofstream::trunc | std::ofstream::out);
            out.write(html.data(), html.size());
            out.close();
        }

        callback(html);
    });
}

static void download_image(StaticGrid* grid, const std::string& url)
{
    download(url, [grid, url](const HttpClientRequest::buffer_type & data)
    {
        // this is silly, we have the data passed as data but still load from file
        auto filename = detail::extract_filename(url);
        if (!filename.empty())
        {
            cout << "loading file " << filename << endl;
            auto surface = detail::image_cache().get(filename);
            if (surface)
            {
                auto image = make_shared<ImageLabel>(Image(surface));
                image->set_boxtype(Theme::boxtype::none);
                image->set_align(alignmask::expand);
                grid->add(image);
            }
        }
    });

}

template <typename T>
static std::string float_to_string(const T value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << value;
    return out.str();
}

static string utc_string(std::time_t t)
{
    char buf[100] = {0};
    std::strftime(buf, sizeof(buf), "%B %d %r", std::localtime(&t));
    return buf;
}

int main(int argc, const char** argv)
{
    Application app(argc, argv, "weather");

    string key;
    string city;
    string country;

    if (argc > 2)
    {
        key = argv[1];
        city = argv[2];
    }
    else
    {
        cerr << "weather KEY CITY [COUNTRY]" << endl;
        return 1;
    }

    if (argc > 3)
        country = argv[3];

    ostringstream ss;
    ss << "https://api.openweathermap.org/data/2.5/weather?appid=" << key << "&units=imperial&q=" << city;
    if (!country.empty())
        ss << "," << country;

    auto url = ss.str();

    TopWindow win;
    auto i = Image("background.jpg");
    auto img = make_shared<ImageLabel>(i);
    img->set_align(alignmask::expand);
    img->set_image_align(alignmask::expand);
    win.add(img);

    StaticGrid grid(Rect(0, 0, 400, 250), Tuple(1, 5), 10);
    win.add(grid);
    grid.set_align(alignmask::center | alignmask::right);

    auto text = city;
    if (!country.empty())
        text += "," + country;

    auto title = make_shared<Label>(text);
    title->set_font(Font(title->font().face(),
                         title->font().size() + 5,
                         title->font().weight(),
                         title->font().slant()));
    title->set_align(alignmask::center);
    grid.add(title);

    download(url, [&grid](const HttpClientRequest::buffer_type & data)
    {
        string icon;
        string description;
        float temp = 0.;
        time_t dt;
        if (!data.empty())
        {
            Json::CharReaderBuilder b;
            unique_ptr<Json::CharReader> reader(b.newCharReader());
            Json::Value root;
            if (reader->parse(data.data(), data.data() + data.size(), &root, nullptr))
            {
                Json::Value weather = root["weather"][0];
                cout << "id: " << weather["id"].asString() << endl;
                cout << "main: " << weather["main"].asString() << endl;
                description = weather["description"].asString();
                cout << "description: " << description << endl;
                icon = weather["icon"].asString();
                cout << "icon: " << icon << endl;
                Json::Value main = root["main"];
                temp = main["temp"].asFloat();
                cout << "temp: " << temp << endl;
                dt = static_cast<std::time_t>(root["dt"].asInt());
            }
        }

        auto dtlabel = make_shared<Label>(utc_string(dt));
        dtlabel->set_align(alignmask::center);
        grid.add(dtlabel);

        if (temp > 0.)
        {
            auto label = make_shared<Label>(float_to_string(temp) + "°");
            label->set_align(alignmask::center);
            label->set_font(Font(label->font().face(),
                                 label->font().size(),
                                 Font::weightid::bold,
                                 label->font().slant()));
            grid.add(label);
        }

        auto label = make_shared<Label>(description.empty() ? "unable to get weather" : description);
        label->set_align(alignmask::center);
        grid.add(label);

        // download the weather icon
        if (!icon.empty())
        {
            ostringstream ss;
            ss << "http://openweathermap.org/img/w/" << icon << ".png";
            string iurl = ss.str();

            egt::asio::post(Application::instance().event().io(), std::bind(download_image, &grid, iurl));
        }

    }, false);

    win.show();

    return app.run();
}
