
#include "connector.h"

std::string getbindtext(size_t hex);

namespace lith {

	namespace binds {

		void thread() {

			size_t selectedbind = 0;
			bool bind_break = false;

			for (;;) {

				if (!lith::info::verified) {//integrity
					break;
				}
				if (lith::module::clicker::left::bindpressed) {

					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					selectedbind = 1;
					lith::module::clicker::left::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;

					while (lith::module::clicker::left::selectedbind == 0) {

						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }

						std::this_thread::sleep_for(std::chrono::milliseconds(2));

						for (size_t i = 3; i < 256; i++) {

							if (i != 13) {

								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::clicker::left::selectedbind == 0) {

									if (!lith_bind_first_loop) {

										lith::module::clicker::left::selectedbind = i;
										lith::module::clicker::left::bind = getbindtext(i);

										if (i == 27) {
											lith::module::clicker::left::bind = "[NONE]";
											selectedbind = 1;
											lith::module::clicker::left::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::clicker::left::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::clicker::left::selectedbind) & 0x8000) {
					if (!lith::module::clicker::left::enabled) {
						while (GetAsyncKeyState(lith::module::clicker::left::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::clicker::left::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::clicker::left::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::clicker::left::enabled = false;
					}
				}

				if (lith::module::clicker::right::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::clicker::right::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::clicker::right::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::clicker::right::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::clicker::right::selectedbind = i; lith::module::clicker::right::bind = getbindtext(i);
										if (i == 27) {
											lith::module::clicker::right::bind = "[NONE]";
											selectedbind = 1;
											lith::module::clicker::right::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::clicker::right::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::clicker::right::selectedbind) & 0x8000) {
					if (!lith::module::clicker::right::enabled) {
						while (GetAsyncKeyState(lith::module::clicker::right::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::clicker::right::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::clicker::right::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::clicker::right::enabled = false;
					}
				}

				if (lith::module::velocity::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::velocity::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::velocity::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::velocity::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::velocity::selectedbind = i; lith::module::velocity::bind = getbindtext(i);
										if (i == 27) {
											lith::module::velocity::bind = "[NONE]";
											selectedbind = 1;
											lith::module::velocity::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::velocity::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
					if (!lith::module::velocity::enabled) {
						while (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::velocity::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::velocity::enabled = false;
					}
				}

				if (lith::module::reach::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::reach::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::reach::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::reach::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::reach::selectedbind = i; lith::module::reach::bind = getbindtext(i);
										if (i == 27) {
											lith::module::reach::bind = "[NONE]";
											selectedbind = 1;
											lith::module::reach::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::reach::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::reach::selectedbind) & 0x8000) {
					if (!lith::module::reach::enabled) {
						while (GetAsyncKeyState(lith::module::reach::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::reach::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::reach::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::reach::enabled = false;
					}
				}

				if (lith::module::velocity::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::velocity::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::velocity::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::velocity::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::velocity::selectedbind = i; lith::module::velocity::bind = getbindtext(i);
										if (i == 27) {
											lith::module::velocity::bind = "[NONE]";
											selectedbind = 1;
											lith::module::velocity::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::velocity::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
					if (!lith::module::velocity::enabled) {
						while (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::velocity::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::velocity::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::velocity::enabled = false;
					}
				}

				if (lith::module::throwpot::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::throwpot::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::throwpot::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::throwpot::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::throwpot::selectedbind = i; lith::module::throwpot::bind = getbindtext(i);
										if (i == 27) {
											lith::module::throwpot::bind = "[NONE]";
											selectedbind = 1;
											lith::module::throwpot::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::throwpot::bindpressed = false;
						bool_counter++;
					}
				}

				if (lith::module::fly::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::fly::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::fly::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::fly::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::fly::selectedbind = i; lith::module::fly::bind = getbindtext(i);
										if (i == 27) {
											lith::module::fly::bind = "[NONE]";
											selectedbind = 1;
											lith::module::fly::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::fly::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::fly::selectedbind) & 0x8000) {
					if (!lith::module::fly::waiting) {
						if (!lith::module::fly::enabled) {
							while (GetAsyncKeyState(lith::module::fly::selectedbind) & 0x8000) {
								std::this_thread::sleep_for(std::chrono::milliseconds(5));
							}lith::module::fly::enabled = true;
						}
						else {
							while (GetAsyncKeyState(lith::module::fly::selectedbind) & 0x8000) {
								std::this_thread::sleep_for(std::chrono::milliseconds(5));
							}lith::module::fly::enabled = false;
						}
					}
				}

				if (lith::module::nametags::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::nametags::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::nametags::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::nametags::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::nametags::selectedbind = i; lith::module::nametags::bind = getbindtext(i);
										if (i == 27) {
											lith::module::nametags::bind = "[NONE]";
											selectedbind = 1;
											lith::module::nametags::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::nametags::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::nametags::selectedbind) & 0x8000) {
					if (!lith::module::nametags::enabled) {
						while (GetAsyncKeyState(lith::module::nametags::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::nametags::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::nametags::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::nametags::enabled = false;
					}
				}

				if (lith::module::esp::bindpressed) {

					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					selectedbind = 1;
					lith::module::esp::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;

					while (lith::module::esp::selectedbind == 0) {

						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }

						std::this_thread::sleep_for(std::chrono::milliseconds(2));

						for (size_t i = 3; i < 256; i++) {

							if (i != 13) {

								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::esp::selectedbind == 0) {

									if (!lith_bind_first_loop) {

										lith::module::esp::selectedbind = i;
										lith::module::esp::bind = getbindtext(i);

										if (i == 27) {
											lith::module::esp::bind = "[NONE]";
											selectedbind = 1;
											lith::module::esp::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::esp::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::esp::selectedbind) & 0x8000) {
					if (!lith::module::esp::enabled) {
						while (GetAsyncKeyState(lith::module::esp::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::esp::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::esp::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::esp::enabled = false;
					}
				}

				if (lith::module::cavefinder::bindpressed) {

					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					selectedbind = 1;
					lith::module::cavefinder::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;

					while (lith::module::cavefinder::selectedbind == 0) {

						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }

						std::this_thread::sleep_for(std::chrono::milliseconds(2));

						for (size_t i = 3; i < 256; i++) {

							if (i != 13) {

								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::cavefinder::selectedbind == 0) {

									if (!lith_bind_first_loop) {

										lith::module::cavefinder::selectedbind = i;
										lith::module::cavefinder::bind = getbindtext(i);

										if (i == 27) {
											lith::module::cavefinder::bind = "[NONE]";
											selectedbind = 1;
											lith::module::cavefinder::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::cavefinder::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::cavefinder::selectedbind) & 0x8000) {
					if (!lith::module::cavefinder::enabled) {
						while (GetAsyncKeyState(lith::module::cavefinder::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::cavefinder::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::cavefinder::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::cavefinder::enabled = false;
					}
				}

				if (lith::module::timer::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::timer::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::timer::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::timer::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::timer::selectedbind = i; lith::module::timer::bind = getbindtext(i);
										if (i == 27) {
											lith::module::timer::bind = "[NONE]";
											selectedbind = 1;
											lith::module::timer::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::timer::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::timer::selectedbind) & 0x8000) {
					if (!lith::module::timer::enabled) {
						while (GetAsyncKeyState(lith::module::timer::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::timer::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::timer::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::timer::enabled = false;
					}
				}

				if (lith::module::bhop::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::bhop::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::bhop::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::bhop::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::bhop::selectedbind = i; lith::module::bhop::bind = getbindtext(i);
										if (i == 27) {
											lith::module::bhop::bind = "[NONE]";
											selectedbind = 1;
											lith::module::bhop::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::bhop::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::bhop::selectedbind) & 0x8000) {
					if (!lith::module::bhop::enabled) {
						while (GetAsyncKeyState(lith::module::bhop::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::bhop::enabled = true;
					}
					else {
						while (GetAsyncKeyState(lith::module::bhop::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::bhop::enabled = false;
					}
				}

				if (lith::module::destruct::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::destruct::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::destruct::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::destruct::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::destruct::selectedbind = i; lith::module::destruct::bind = getbindtext(i);
										if (i == 27) {
											lith::module::destruct::bind = "[NONE]";
											selectedbind = 1;
											lith::module::destruct::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::destruct::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::destruct::selectedbind) & 0x8000) {
					
					lith::module::destruct::execute();

				}

				if (lith::module::hide::bindpressed) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					selectedbind = 1;
					lith::module::hide::selectedbind = 0;
					bool lith_bind_first_loop = false; size_t bool_counter = 0;
					while (lith::module::hide::selectedbind == 0) {
						if (bool_counter < 1) { lith_bind_first_loop = true; }
						else { lith_bind_first_loop = false; }
						std::this_thread::sleep_for(std::chrono::milliseconds(2));
						for (size_t i = 3; i < 256; i++) {
							if (i != 13) {
								if (GetAsyncKeyState((i)&SHRT_MAX) && lith::module::hide::selectedbind == 0) {
									if (!lith_bind_first_loop) {
										lith::module::hide::selectedbind = i; lith::module::hide::bind = getbindtext(i);
										if (i == 27) {
											lith::module::hide::bind = "[NONE]";
											selectedbind = 1;
											lith::module::hide::selectedbind = 0;
											bind_break = true;
										}
										std::this_thread::sleep_for(std::chrono::milliseconds(250));
									}
								}
							}
						}
						if (bind_break) { bind_break = false; break; }
						selectedbind = 0;
						lith::module::hide::bindpressed = false;
						bool_counter++;
					}
				}
				if (GetAsyncKeyState(lith::module::hide::selectedbind) & 0x8000) {
					if (!lith::module::hide::enabled) {
						ShowWindow(lith::gui::hwnd, SW_HIDE);
						while (GetAsyncKeyState(lith::module::hide::selectedbind) & 0x8000) {
							std::this_thread::sleep_for(std::chrono::milliseconds(5));
						}lith::module::hide::enabled = true;
					}
					else {
						ShowWindow(lith::gui::hwnd, SW_SHOW);
						while (GetAsyncKeyState(lith::module::hide::selectedbind) & 0x8000) {

							std::this_thread::sleep_for(std::chrono::milliseconds(5));

						}
						lith::module::hide::enabled = false;
					}

				}

				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}

		}

	}

}


std::string getbindtext(size_t hex) {
	const char* const lith_key_string[] = {
		"Unknown",
		"LButton",
		"RButton",
		"CANCEL",
		"MButton",
		"MButton2",
		"MButton3",
		"Unknown",
		"Back",
		"Tab",
		"Unknown",
		"Unknown",
		"Clear",
		"Return",
		"Unknown",
		"Unknown",
		"Shift",
		"Control",
		"Menu",
		"Pause",
		"Capital",
		"Unknown",
		"Unknown",
		"Unknown",
		"Final",
		"Unknown",
		"Unknown",
		"Escape",
		"Convert",
		"NonConvert",
		"Accept",
		"ModeChange",
		"Space",
		"Prior",
		"Next",
		"End",
		"Home",
		"Left",
		"Up",
		"Right",
		"Down",
		"Select",
		"Print",
		"Execute",
		"SnpShot",
		"Insert",
		"Delete",
		"Help",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Lwin",
		"Rwin",
		"Apps",
		"Unknown",
		"Sleep",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"*",
		"+",
		"Separator",
		"-",
		"Decimal",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"F16",
		"F17",
		"F18",
		"F19",
		"F20",
		"F21",
		"F22",
		"F23",
		"F24",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Numlock",
		"Scroll",
		"Equal",
		"Masshou",
		"Touroku",
		"Loya",
		"Roya",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"LShift",
		"RShift",
		"Control",
		"Control",
		"Menu",
		"RMenu"
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
		"Unknown",
	};
	return "[Bind: " + std::string(lith_key_string[hex]) + "]";
}