
#include "../misc/connector.h"


int getbindcode(int lith_throwpot_slot)
{
	if (lith_throwpot_slot == 1) { return lith::localplayer::binds::slot1; }
	if (lith_throwpot_slot == 2) { return lith::localplayer::binds::slot2; }
	if (lith_throwpot_slot == 3) { return lith::localplayer::binds::slot3; }
	if (lith_throwpot_slot == 4) { return lith::localplayer::binds::slot4; }
	if (lith_throwpot_slot == 5) { return lith::localplayer::binds::slot5; }
	if (lith_throwpot_slot == 6) { return lith::localplayer::binds::slot6; }
	if (lith_throwpot_slot == 7) { return lith::localplayer::binds::slot7; }
	if (lith_throwpot_slot == 8) { return lith::localplayer::binds::slot8; }
	if (lith_throwpot_slot == 9) { return lith::localplayer::binds::slot9; }
	return 0;
}

bool thrown = false;
size_t position = 0;

namespace lith {
	namespace module {
		namespace throwpot {
			void thread() {
				for (;;) {
					if (!lith::info::verified) {//integrity
						break;
					}
					while (lith::module::throwpot::enabled) {
						if (GetAsyncKeyState(lith::module::throwpot::selectedbind) & 0x8000) {
							POINT P; GetCursorPos(&P);
							HWND window = WindowFromPoint(P);
							if (ScreenToClient(window, &P)) {
								if (!lith::localplayer::inventoryopen) {
									if (FindWindow(("LWJGL"), nullptr) == GetForegroundWindow()) {
										while (!thrown) {
											for (size_t i = 0; i < 9; ++i) {
												if (i == position) {
													if (lith::module::throwpot::slot[i]) {

														POINT pos1;
														GetCursorPos(&pos1);
														HWND window = WindowFromPoint(pos1);

														if (ScreenToClient(window, &pos1)) {

															keybd_event(getbindcode(i + 1), 0, 0, 0);
															keybd_event(getbindcode(i + 1), 0, KEYEVENTF_KEYUP, 0);
															lith::localplayer::current_slot = i + 1;

															SendMessage(window, WM_RBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos1.x, pos1.y));
															std::this_thread::sleep_for(std::chrono::milliseconds((int)lith::tools::getrandomfloat(lith::module::throwpot::value * 0.75, lith::module::throwpot::value * 1.25)));
															SendMessage(window, WM_RBUTTONUP, MK_LBUTTON, MAKELPARAM(pos1.x, pos1.y));

															if (lith::module::throwpot::throw_item) {

																keybd_event(lith::localplayer::binds::drop, 0, 0, 0);
																keybd_event(lith::localplayer::binds::drop, 0, KEYEVENTF_KEYUP, 0);

															}

															keybd_event(getbindcode(lith::module::throwpot::return_pos), 0, 0, 0);
															keybd_event(getbindcode(lith::module::throwpot::return_pos), 0, KEYEVENTF_KEYUP, 0);
															lith::localplayer::current_slot = lith::module::throwpot::return_pos;
														
														}

														position++;
														thrown = true;
														break;

													}
													else {
														position++;
													}
												}
											}
											if (position >= 9) { position = 0; }
											std::this_thread::sleep_for(std::chrono::milliseconds(1));
										}
										thrown = false;
										while (GetAsyncKeyState(lith::module::throwpot::selectedbind) & 0x8000) { std::this_thread::sleep_for(std::chrono::milliseconds(1)); }
									}
								}
							}

						}
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
		}
	}
}
