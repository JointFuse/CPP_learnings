#include "TextGraph.h"
#include "Text.h"
#include <FL/FL_Multiline_Output.H>
#include <FL/Fl_Round_Button.H>
#include <sstream>
#include <fstream>

using namespace TextGraph_lib;
using namespace Sizes;

//------------------------------------------------------------------------------

void Multiline_out_box::put(const string& s)
{
    reference_to<Fl_Multiline_Output>(pw).value(s.c_str());
}

//------------------------------------------------------------------------------

void Multiline_out_box::set_textsize(int s)
{
    reference_to<Fl_Multiline_Output>(pw).textsize(s);
}

//------------------------------------------------------------------------------

void Multiline_out_box::attach(Window& win)
{
    pw = new Fl_Multiline_Output(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

void Binary_button::attach(Window& win)
{
    pw = new Fl_Round_Button(loc.x, loc.y, width, height, label.c_str());
    own = &win;
}

//------------------------------------------------------------------------------

bool Binary_button::state()
{
    return static_cast<Fl_Round_Button*>(pw)->value();
}

//------------------------------------------------------------------------------

Text_interface::Text_interface(Point xy)
    : Window(xy, width, height, "mYcrosoft word"),
    out_main({ xofs, yofs }, outboxwid, outboxlen, ""),
    in_filename({ xofs + outboxwid + texofs, yofs }, 
                boxlen1, boxheight, "file:"),
    in_key({ xofs + outboxwid + texofs, yofs + boxheight * 4 }, 
           boxlen1, boxheight, "key:"),
    b_loadfile({ xofs + outboxwid + texofs + boxlen1, yofs },
               boxlen1, boxheight, "upload", cb_loadfile),
    b_lexsearch({ xofs + outboxwid + texofs + boxlen1, yofs + boxheight * 4 },
                boxlen1, boxheight, "name", cb_lexsearch),
    b_sizesearch({ xofs + outboxwid + texofs + boxlen1, yofs + boxheight * 5 },
                 boxlen1, boxheight, "lenght", cb_sizesearch),
    b_cntword({ xofs + outboxwid + texofs, yofs + boxheight * 5 },
              boxlen1, boxheight, "count", cb_cntword),
    b_mostcnt({ xofs + outboxwid + texofs, yofs + boxheight * 7 },
              boxlen2, boxheight, "most count", cb_mostcnt),
    b_longest({ xofs + outboxwid + texofs, yofs + boxheight * 8 }, 
              boxlen2, boxheight, "longest", cb_longest),
    b_shortest({ xofs + outboxwid + texofs, yofs + boxheight * 9 },
               boxlen2, boxheight, "shortest", cb_shortest),
    b_quit({ xofs + outboxwid + texofs, yofs + outboxlen - boxheight }, 
           boxlen2, boxheight, "quit", cb_quit),
    b_dictset({ xofs + outboxwid + texofs, yofs + boxheight },
              boxlen2, boxheight, "use dictionary"),
    b_dictupd({ xofs + outboxwid + texofs, yofs + boxheight * 2 },
              boxlen2, boxheight, "update dictionary")
{
    attach(out_main);
    attach(in_filename);
    attach(in_key);
    attach(b_loadfile);
    attach(b_lexsearch);
    attach(b_sizesearch);
    attach(b_cntword);
    attach(b_mostcnt);
    attach(b_longest);
    attach(b_shortest);
    attach(b_quit);
    attach(b_dictset);
    attach(b_dictupd);
}

//------------------------------------------------------------------------------

void Text_interface::f_loadfile()
{
    ostringstream info;
    string fname{ in_filename.get_string() };
    bool singles_loaded{ false }, singles_stored{ false };

    try {
        ifstream opend{fname + Text_lib::file_predicate + Text_lib::file_format };
        if (!opend) {
            if (b_dictset.state())
                { singles_loaded = Text_lib::load_singles(); }
            Text_lib::make_dictionary(fname);
            if (b_dictupd.state())
                { singles_stored = Text_lib::store_singles(!singles_loaded); }
            info << "File \"" << fname << "\" loaded sucessfully" << '\n';
        }
        else 
            { info << "File \"" << fname << "\" already loaded" << '\n'; }
    }
    catch (runtime_error& err) {
        singles_loaded = false;
        info << "Error loading file \"" << fname << "\":\n" 
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::folder_err << '\n'
             << " - " << ErrText::name_err << '\n';
    }

    
     info << "Single's dictionary [ " << (singles_loaded ? "used" : "not used")
          << (singles_stored ? " and updated" : "") << " ]";

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_cntword()
{
    string word{ in_key.get_string() };
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        int count = Text_lib::count_word(fname + Text_lib::file_predicate, word);
        info << "Total count of \"" << word << "\" in file \""
             << fname << "\" = " << count << '\n';
    }
    catch (runtime_error& err) {
        info << "Error counting word in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_mostcnt()
{
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        string word = Text_lib::most_counted_word(fname + Text_lib::file_predicate);
        info << "Most counted word in file \"" << fname << "\" = " << word << '\n';
    }
    catch (runtime_error& err) {
        info << "Error searching most counted word in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_longest()
{
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        string word = Text_lib::longest_word(fname + Text_lib::file_predicate);
        info << "Longest word in file \"" << fname << "\" = " << word << '\n';
    }
    catch (runtime_error& err) {
        info << "Error searching longest word in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_shortest()
{
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        string word = Text_lib::shortest_word(fname + Text_lib::file_predicate);
        info << "Shortest word in file \"" << fname << "\" = " << word << '\n';
    }
    catch (runtime_error& err) {
        info << "Error searching shortest word in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_sizesearch()
{
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        int lenght = in_key.get_int();
        vector<string> word = Text_lib::all_by_length(fname + Text_lib::file_predicate, lenght);
        sort(word.begin(), word.end());
        auto p = unique(word.begin(), word.end());

        info << "All words that lenght = " << lenght << " in file \"" << fname << "\": {\n";
        for_each(word.begin(), p, [&](const string& s) { info << '\t' << s << '\n'; });
        info << "};\n";
    }
    catch (runtime_error& err) {
        info << "Error searching words that lenght = key in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------

void Text_interface::f_lexsearch()
{
    ostringstream info;
    string fname{ in_filename.get_string() };

    try {
        string pred = in_key.get_string();
        vector<string> word = Text_lib::all_starting_by(fname + Text_lib::file_predicate, pred);
        sort(word.begin(), word.end());
        auto p = unique(word.begin(), word.end());

        info << "All words starting by \"" << pred << "\" in file \"" << fname << "\": {\n";
        for_each(word.begin(), p, [&](const string& s) { info << '\t' << s << '\n'; });
        info << "};\n";
    }
    catch (runtime_error& err) {
        info << "Error searching words starting by key in file \"" << fname << "\":\n"
             << "Message:\t" << err.what() << '\n'
             << " - " << ErrText::name_err << '\n'
             << " - " << ErrText::opend_err << '\n';
    }

    out_main.put(info.str());
}

//------------------------------------------------------------------------------
