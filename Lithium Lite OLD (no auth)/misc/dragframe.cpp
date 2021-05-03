
#include "connector.h"

namespace lith {

	namespace gui {

		void move_window() {

			for (;;) {

				if (!lith::info::verified) {//integrity
					break;
				}
				if (lith::gui::window_being_dragged) {

					if (!lith::gui::item_being_used) {

						POINT t;

						if (GetCursorPos(&t)) {

							if (HWND window = WindowFromPoint(t)) {

								if (ScreenToClient(window, &t)) {

									while (lith::gui::window_being_dragged) {

										POINT p;

										if (GetCursorPos(&p)) {

											if (lith::info::verified) {

												SetWindowPos(lith::gui::hwnd, NULL, p.x - t.x, p.y - t.y, 720, 530, SWP_FRAMECHANGED);

											}

										}

										std::this_thread::sleep_for(std::chrono::milliseconds(1));
									}

								}

							}

						}

					}

				} 

				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}

		}

	}

}