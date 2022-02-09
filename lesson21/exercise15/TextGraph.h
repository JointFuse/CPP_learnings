#ifndef TextGraph_h
#define TextGraph_h

#include "GUI/Window.h"
#include "GUI/my_graph.h"
#include "GUI/Point.h"
#include <map>

namespace TextGraph_lib {
	using namespace Graph_lib;

    //------------------------------------------------------------------------------

    namespace Sizes {
        constexpr int x_frame{ 8 };
        constexpr int y_frame{ 8 };
        constexpr int xofs{ 20 };
        constexpr int yofs{ 20 };
        constexpr int texofs{ 40 };
        constexpr int boxheight{ 25 };
        constexpr int boxlen1{ 60 };
        constexpr int boxlen2{ boxlen1 * 2 };
        constexpr int outboxwid{ 400 };
        constexpr int outboxlen{ 400 };
        constexpr int width{ xofs * 2 + texofs + boxlen2
                             + outboxwid + x_frame };
        constexpr int height{ yofs * 2 + outboxlen + y_frame };
    }

    namespace ErrText {
        const string folder_err{ "file may not be in the programm folder" };
        const string name_err{ "file name may be entered incorrectly" };
        const string opend_err{ "file may not have been uploaded" };
    }

    //------------------------------------------------------------------------------

    struct Multiline_out_box : Widget {
        Multiline_out_box(Point xy, int w, int h, const string& s)
            :Widget(xy, w, h, s, 0) { }
        void put(const string&);

        void set_textsize(int s);

        void attach(Window& win);
    };

    //------------------------------------------------------------------------------

    struct Binary_button : Widget {
        Binary_button(Point xy, int w, int h, const string& label)
            : Widget(xy, w, h, label) { }

        void attach(Window&);
        bool state();
    };
    
    //------------------------------------------------------------------------------

    class Text_interface : Window {
        // Vidges
        Multiline_out_box out_main;
        In_box in_filename;
        In_box in_key;

        Button b_loadfile;
        Button b_lexsearch;
        Button b_sizesearch;
        Button b_cntword;
        Button b_mostcnt;
        Button b_longest;
        Button b_shortest;
        Button b_quit;
        
        Binary_button b_dictset;
        Binary_button b_dictupd;

        // button functions
        void f_loadfile();
        void f_cntword();
        void f_mostcnt();
        void f_longest();
        void f_shortest();
        void f_sizesearch();
        void f_lexsearch();
        void f_quit() { hide(); throw runtime_error("program stoped"); }

        // Call back funstions
        static void cb_loadfile(Address, Address pw)    { reference_to<Text_interface>(pw).f_loadfile(); }
        static void cb_cntword(Address, Address pw)     { reference_to<Text_interface>(pw).f_cntword(); }
        static void cb_mostcnt(Address, Address pw)     { reference_to<Text_interface>(pw).f_mostcnt(); }
        static void cb_longest(Address, Address pw)     { reference_to<Text_interface>(pw).f_longest(); }
        static void cb_shortest(Address, Address pw)    { reference_to<Text_interface>(pw).f_shortest(); }
        static void cb_sizesearch(Address, Address pw)  { reference_to<Text_interface>(pw).f_sizesearch(); }
        static void cb_lexsearch(Address, Address pw)   { reference_to<Text_interface>(pw).f_lexsearch(); }
        static void cb_quit(Address, Address pw)        { reference_to<Text_interface>(pw).f_quit(); }
    public:
        Text_interface(Point xy);
    };
}
#endif	// !TextGraph_h