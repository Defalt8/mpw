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
		// window.on_move = [&](int x, int y) { mw::log << "posi " << x << " " << y << mw::endl; };
		// window.on_size = [&](int w, int h) { mw::log << "size " << w << " " << h << mw::endl; };
		// window.on_mouse_button = [&](int x, int y, mw::mouse_button btn, bool down) { mw::log << "mouse button " << cstr_mouse_button(btn) << " " << down << "  " << x << " " << y << mw::endl; };
		// window.on_mouse_move   = [&](int x, int y) { mw::log << "mouse move " << "  " << x << " " << y << mw::endl; };
		// window.on_mouse_wheel  = [&](int x, int y, int delta, bool vertical) { mw::log << "mouse wheel " << x << " " << y << " " << delta << " " << vertical << mw::endl; };
		// window.on_key = [&](mw::key key, bool down) { mw::log << "key " << cstr_key(key) << " " << down << mw::endl; };
		bool mbtn_left_down  = false;
		bool mbtn_right_down = false;
		int  pwin_x = 0, pwin_y = 0;
		int  lbtn_x = 0, lbtn_y = 0;
		int  rbtn_x = 0, rbtn_y = 0;
		int  pbtn_x = 0, pbtn_y = 0;
		bool show_cursor = true;
		window.on_key = [&](mw::key key, bool down)
		{
			if(key == mw::key_h && !down)
			{
				show_cursor = !show_cursor;
				window.show_cursor(show_cursor);
				mw::log << (show_cursor ? "show" : "hide") << mw::endl;
			}
		};
		window.on_mouse_button = [&](int x, int y, mw::mouse_button btn, bool down) 
		{
			if(btn == mw::mb_left)
			{
				mbtn_left_down = down;
				if(mbtn_left_down)
				{
					pwin_x = window.x();
					pwin_y = window.y();
					window.get_cursor_position(lbtn_x, lbtn_y);
				}
			}
			else if(btn == mw::mb_right)
			{
				mbtn_right_down = down;
				window.get_cursor_position(rbtn_x, rbtn_y);
			}
		};
		window.on_mouse_move   = [&](int x, int y) 
		{
			if(mbtn_right_down)
			{
				int c_x, c_y;
				if(window.get_cursor_position(c_x, c_y) && (c_x != rbtn_x || c_y != rbtn_y))
				{
					int d_x = c_x - rbtn_x;
					int d_y = c_y - rbtn_y;
					mw::log << d_x << " " << d_y << "      \r" << mw::endl;
					window.set_cursor_position(rbtn_x, rbtn_y);
				}
			}
		};
		window.enable_vsync();
		assert(window.show());
		mw::log << (char const *)glGetString(GL_VERSION) << mw::endl;
		mw::log << "testing: get_cursor_position -- using left mouse button" << mw::endl;
		mw::log << "testing: set_cursor_position -- using right mouse button" << mw::endl;
		mw::log << "testing: show_cursor -- using key h" << mw::endl;
		while(window)
		{
			if(mbtn_left_down)
			{
				int x = 0, y = 0;
				if(window.get_cursor_position(x, y) && (x != pbtn_x || y != pbtn_y))
				{
					mw::log << x << " " << y << mw::endl;
					pbtn_x = x; pbtn_y = y;
					int win_x = pwin_x + (x - lbtn_x);
					int win_y = pwin_y + (y - lbtn_y);
					window.set_position(win_x, win_y);
				}
			}
			while(mw::next_event(display, event, false) && mw::process_event(event));
			if(window.make_current()) 
			{
				float ct = float(clock()) / float(CLOCKS_PER_SEC);
				float v1 = 0.5f * (1.f + cos(ct));
				float v2 = 0.5f * (1.f + sin(1.38f * ct));
				float v3 = 0.5f * (1.f + cos(-0.9f * ct));
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
