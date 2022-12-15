#include <mpw/all>
#include <ds/all>
#ifdef _WIN32
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#endif
#include <GL/gl.h>

int main()
{
	ds_try {
		mw::display display; 
		mw::event   event;
		mw::window  window(display, "main window", 640, 480);
		window.on_move = [&](int x, int y) { mw::log << "posi " << x << " " << y << mw::endl; };
		window.on_size = [&](int w, int h) { mw::log << "size " << w << " " << h << mw::endl; };
		window.on_mouse_button = [&](int x, int y, mw::mouse_button btn, bool down) { mw::log << "mouse button " << cstr_mouse_button(btn) << " " << down << "  " << x << " " << y << mw::endl; };
		window.on_mouse_move   = [&](int x, int y) { mw::log << "mouse move " << "  " << x << " " << y << mw::endl; };
		window.on_mouse_wheel  = [&](int x, int y, int delta, bool vertical) { mw::log << "mouse wheel " << x << " " << y << " " << delta << " " << vertical << mw::endl; };
		window.on_key = [&](mw::key key, bool down) { mw::log << "key " << cstr_key(key) << " " << down << mw::endl; };
		window.enable_vsync();
		assert(window.show());
		mw::log << (char const *)glGetString(GL_VERSION) << mw::endl;
		while(window)
		{
			mw::next_event(display, event, false) && mw::process_event(event);
			if(window.make_current()) 
			{
				float ct = float(clock()) / float(CLOCKS_PER_SEC);
				float v1 = 1.f + cos(ct);         if(v1 > 1.f) v1 = 2.f - v1;
				float v2 = 1.f + sin(1.38f * ct); if(v2 > 1.f) v2 = 2.f - v2;
				float v3 = 1.f + cos(-0.9f * ct); if(v3 > 1.f) v3 = 2.f - v3;
				glClearColor(v1, v2, v3, 1.f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				window.swap();
			}
		}
	}
	ds_catch_block(ds::exception const & ex,
	{
		mw::log << ex.what() << mw::endl_error;
	});
}
