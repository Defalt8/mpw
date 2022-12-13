#include <mpw/all>
#include <ds/all>

int main()
{
	ds_try {
		mw::init();
		mw::display display; 
		mw::event   event;
		mw::window  window(display, "main window", 640, 480);
		window.on_move = [&](int x, int y) { mw::log << "posi " << x << " " << y << mw::endl; };
		window.on_size = [&](int w, int h) { mw::log << "size " << w << " " << h << mw::endl; };
		window.on_mouse_button = [&](int x, int y, mw::mouse_button btn, bool down) { mw::log << "mouse button " << cstr_mouse_button(btn) << " " << down << "  " << x << " " << y << mw::endl; };
		window.on_mouse_move   = [&](int x, int y) { mw::log << "mouse move " << "  " << x << " " << y << mw::endl; };
		window.on_mouse_wheel  = [&](int x, int y, int delta, bool vertical) { mw::log << "mouse wheel " << x << " " << y << " " << delta << " " << vertical << "  " << mw::endl; };
		assert(window.show());
		mw::log << (char const *)glfl::GL::get_string(glfl::GL::VERSION) << mw::endl;
		while(window)
		{
			mw::next_event(display, event, false) && mw::process_event(event);
			if(window.make_current()) 
			{
				using namespace glfl::GL;
				float v = fmodf(float(clock()) / float(CLOCKS_PER_SEC), 1.f);
				clear_color(v, .2f, .3f, 0.f);
				clear(COLOR_BUFFER_BIT | DEPTH_BUFFER_BIT);
				window.swap();
			}
		}
	}
	ds_catch_block(ds::exception const & ex,
	{
		mw::log << ex.what() << mw::endl_error;
	});
}
