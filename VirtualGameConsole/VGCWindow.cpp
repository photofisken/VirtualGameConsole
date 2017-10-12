#include "VGCWindow.h"
#include "VGCBus.h"
#include <windows.h>
#include <tchar.h>
#include <string>



/* File scope data */
static const char fWindowClassName[]            = "VGCWindowClass";
static int        fInitializeMinusFinalizeCount = 0;
static HWND       fWindowHandle                 = NULL;
static bool       fWindowIsOpen                 = false;


/* File scope functions */
static bool fInvariant(){
	return ((NULL != fWindowHandle) && (0 < fInitializeMinusFinalizeCount));
}

static void fSetWindowClientSize(HWND windowHandle, int width, int height){
	VGCAssert(NULL != windowHandle);
	VGCAssert(0 <= width);
	VGCAssert(0 <= height);

	RECT windowRectangle;
	RECT clientRectangle;
	GetWindowRect(windowHandle, &windowRectangle);
	GetClientRect(windowHandle, &clientRectangle);
	const LONG WINDOW_WIDTH  = (windowRectangle.right - windowRectangle.left);
	const LONG WINDOW_HEIGHT = (windowRectangle.bottom - windowRectangle.top);
	const LONG CLIENT_WIDTH  = (clientRectangle.right - clientRectangle.left);
	const LONG CLIENT_HEIGHT = (clientRectangle.bottom - clientRectangle.top);
	const LONG NEW_X         = windowRectangle.left;
	const LONG NEW_Y         = windowRectangle.top;	
	const LONG NEW_WIDTH     = (WINDOW_WIDTH + (width - CLIENT_WIDTH));
	const LONG NEW_HEIGHT    = (WINDOW_HEIGHT + (height - CLIENT_HEIGHT));
	BOOL result = MoveWindow(windowHandle, NEW_X, NEW_Y, NEW_WIDTH, NEW_HEIGHT, FALSE);
	VGCAssert(result && "Window moved/resized successfully.");
}


static LRESULT fHandleCharacterMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	VGCAssert(WM_CHAR == message);

	const char CHARACTER        = char(wParam);
	const int  REPETITION_COUNT = int(lParam & 0xffff);
	for(int i = 0; i < REPETITION_COUNT; i++){
		VGCBus::postMessage(VGCCharacterMessage(CHARACTER));
	}
	return 0;
}

static VGCKey fGetKey(int keyCode){
	VGCKey key = VGCKey::NULL_KEY;
	switch(keyCode){
	case VK_BACK:
		key = VGCKey::BACKSPACE_KEY;
		break;
	case VK_TAB:
		key = VGCKey::TAB_KEY;
		break;
	case VK_RETURN:
		key = VGCKey::RETURN_KEY;
		break;
	case VK_SHIFT:
		key = VGCKey::SHIFT_KEY;
		break;
	case VK_CONTROL:
		key = VGCKey::CONTROL_KEY;
		break;
	case VK_MENU:
		key = VGCKey::MENU_KEY;
		break;
	case VK_ESCAPE:
		key = VGCKey::ESCAPE_KEY;
		break;
	case VK_SPACE:
		key = VGCKey::SPACE_KEY;
		break;
	case VK_PRIOR:
		key = VGCKey::PAGE_UP_KEY;
		break;
	case VK_NEXT:
		key = VGCKey::PAGE_DOWN_KEY;
		break;
	case VK_END:
		key = VGCKey::END_KEY;
		break;
	case VK_HOME:
		key = VGCKey::HOME_KEY;
		break;
	case VK_LEFT:
		key = VGCKey::ARROW_LEFT_KEY;
		break;
	case VK_UP:
		key = VGCKey::ARROW_UP_KEY;
		break;
	case VK_RIGHT:
		key = VGCKey::ARROW_RIGHT_KEY;
		break;
	case VK_DOWN:
		key = VGCKey::ARROW_DOWN_KEY;
		break;
	case VK_DELETE:
		key = VGCKey::DELETE_KEY;
		break;
	case '0':
		key = VGCKey::ZERO_KEY;
		break;
	case '1':
		key = VGCKey::ONE_KEY;
		break;
	case '2':
		key = VGCKey::TWO_KEY;
		break;
	case '3':
		key = VGCKey::THREE_KEY;
		break;
	case '4':
		key = VGCKey::FOUR_KEY;
		break;
	case '5':
		key = VGCKey::FIVE_KEY;
		break;
	case '6':
		key = VGCKey::SIX_KEY;
		break;
	case '7':
		key = VGCKey::SEVEN_KEY;
		break;
	case '8':
		key = VGCKey::EIGHT_KEY;
		break;
	case '9':
		key = VGCKey::NINE_KEY;
		break;
	case 'A':
		key = VGCKey::A_KEY;
		break;
	case 'B':
		key = VGCKey::B_KEY;
		break;
	case 'C':
		key = VGCKey::C_KEY;
		break;
	case 'D':
		key = VGCKey::D_KEY;
		break;
	case 'E':
		key = VGCKey::E_KEY;
		break;
	case 'F':
		key = VGCKey::F_KEY;
		break;
	case 'G':
		key = VGCKey::G_KEY;
		break;
	case 'H':
		key = VGCKey::H_KEY;
		break;
	case 'I':
		key = VGCKey::I_KEY;
		break;
	case 'J':
		key = VGCKey::J_KEY;
		break;
	case 'K':
		key = VGCKey::K_KEY;
		break;
	case 'L':
		key = VGCKey::L_KEY;
		break;
	case 'M':
		key = VGCKey::M_KEY;
		break;
	case 'N':
		key = VGCKey::N_KEY;
		break;
	case 'O':
		key = VGCKey::O_KEY;
		break;
	case 'P':
		key = VGCKey::P_KEY;
		break;
	case 'Q':
		key = VGCKey::Q_KEY;
		break;
	case 'R':
		key = VGCKey::R_KEY;
		break;
	case 'S':
		key = VGCKey::S_KEY;
		break;
	case 'T':
		key = VGCKey::T_KEY;
		break;
	case 'U':
		key = VGCKey::U_KEY;
		break;
	case 'V':
		key = VGCKey::V_KEY;
		break;
	case 'W':
		key = VGCKey::W_KEY;
		break;
	case 'X':
		key = VGCKey::X_KEY;
		break;
	case 'Y':
		key = VGCKey::Y_KEY;
		break;
	case 'Z':
		key = VGCKey::Z_KEY;
		break;
	case VK_NUMPAD0:
		key = VGCKey::PAD_ZERO_KEY;
		break;
	case VK_NUMPAD1:
		key = VGCKey::PAD_ONE_KEY;
		break;
	case VK_NUMPAD2:
		key = VGCKey::PAD_TWO_KEY;
		break;
	case VK_NUMPAD3:
		key = VGCKey::PAD_THREE_KEY;
		break;
	case VK_NUMPAD4:
		key = VGCKey::PAD_FOUR_KEY;
		break;
	case VK_NUMPAD5:
		key = VGCKey::PAD_FIVE_KEY;
		break;
	case VK_NUMPAD6:
		key = VGCKey::PAD_SIX_KEY;
		break;
	case VK_NUMPAD7:
		key = VGCKey::PAD_SEVEN_KEY;
		break;
	case VK_NUMPAD8:
		key = VGCKey::PAD_EIGHT_KEY;
		break;
	case VK_NUMPAD9:
		key = VGCKey::PAD_NINE_KEY;
		break;
	case VK_MULTIPLY:
		key = VGCKey::PAD_MULTIPLY_KEY;
		break;
	case VK_ADD:
		key = VGCKey::PAD_ADD_KEY;
		break;
	case VK_SUBTRACT:
		key = VGCKey::PAD_SUBTRACT_KEY;
		break;
	case VK_DIVIDE:
		key = VGCKey::PAD_DIVIDE_KEY;
		break;
	case VK_F1:
		key = VGCKey::F1_KEY;
		break;
	case VK_F2:
		key = VGCKey::F2_KEY;
		break;
	case VK_F3:
		key = VGCKey::F3_KEY;
		break;
	case VK_F4:
		key = VGCKey::F4_KEY;
		break;
	case VK_F5:
		key = VGCKey::F5_KEY;
		break;
	case VK_F6:
		key = VGCKey::F6_KEY;
		break;
	case VK_F7:
		key = VGCKey::F7_KEY;
		break;
	case VK_F8:
		key = VGCKey::F8_KEY;
		break;
	case VK_F9:
		key = VGCKey::F9_KEY;
		break;
	case VK_F10:
		key = VGCKey::F10_KEY;
		break;
	case VK_F11:
		key = VGCKey::F11_KEY;
		break;
	case VK_F12:
		key = VGCKey::F12_KEY;
		break;
	default:
		key = VGCKey::NULL_KEY;
    break;
  }
  return key;
} 

static LRESULT fHandleKeyMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	VGCAssert((WM_SYSKEYDOWN == message) || (WM_KEYDOWN == message) ||(WM_SYSKEYUP == message) || (WM_KEYUP == message));

	const int                  KEY_CODE         = int(wParam);
	const VGCKey               key              = fGetKey(KEY_CODE);
	const int                  REPETITION_COUNT = int(lParam & 0xffff);
	const VGCKeyMessage::Event event            = 
		((WM_SYSKEYDOWN == message) || (WM_KEYDOWN == message)) ?
		VGCKeyMessage::PRESS_EVENT :
		VGCKeyMessage::RELEASE_EVENT;
	for(int i = 0; i < REPETITION_COUNT; i++){
		VGCBus::postMessage(VGCKeyMessage(event, key));
	}
	return 0;
}

static LRESULT fHandlePaintMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	VGCAssert(NULL != hWnd);
	VGCAssert(WM_PAINT == message);

	VGCBus::postMessage(VGCNotificationMessage(VGCNotificationMessage::PAINT_NOTIFICATION));
	ValidateRect(hWnd, NULL);
	return 0;
}

static LRESULT fHandleDestroyMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	VGCAssert(WM_DESTROY == message);
	
	PostQuitMessage(0);
	return 0;
}

static LRESULT fHandleUnknownMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	LRESULT result = DefWindowProc(hWnd, message, wParam, lParam);
	return result;
}

static LRESULT CALLBACK fWindowCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	LRESULT result;
	switch(message){
	case WM_CHAR:
		result = fHandleCharacterMessage(hWnd, message, wParam, lParam);
		break;
	case WM_SYSKEYDOWN: 
	case WM_KEYDOWN:
	case WM_SYSKEYUP: 
	case WM_KEYUP:
		result = fHandleKeyMessage(hWnd, message, wParam, lParam);
		break;
	case WM_PAINT:
		result = fHandlePaintMessage(hWnd, message, wParam, lParam);
		break;
	case WM_DESTROY:
		result = fHandleDestroyMessage(hWnd, message, wParam, lParam);
		break;
	default:
		result = fHandleUnknownMessage(hWnd, message, wParam, lParam);
		break;
	}
	return result;
}

static void fHandleMessages(){
	MSG message;
	while(PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)){
		if(GetMessage(&message, NULL, 0, 0)){
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else{
			fWindowIsOpen = false;
		}
	}
}



/* VGCWindow */

/* Public functions */
void VGCWindow::finalizeWindow(){
	VGCAssert(fInvariant());
	
	fInitializeMinusFinalizeCount--;
	if(0 == fInitializeMinusFinalizeCount){
		if(fWindowIsOpen){
			BOOL windowDestroyed = DestroyWindow(fWindowHandle);
			VGCAssert(windowDestroyed);
			fHandleMessages();
			fWindowIsOpen = false;
		}

		BOOL windowClassUnregistered = UnregisterClass(fWindowClassName, GetModuleHandle(NULL));
		VGCAssert(windowClassUnregistered);

		VGCBus::finalizeBus();

		VGCAssert(!fInvariant());
	}
}

HWND VGCWindow::getHandle(){
	VGCAssert(fInvariant());

	return fWindowHandle;
}

int VGCWindow::getHeight(){
	VGCAssert(fInvariant());

	RECT clientRectangle;
	GetClientRect(fWindowHandle, &clientRectangle);
	const int WINDOW_HEIGHT = (clientRectangle.bottom - clientRectangle.top);
	VGCAssert(0 <= WINDOW_HEIGHT);
	return WINDOW_HEIGHT;
}

int VGCWindow::getWidth(){
	VGCAssert(fInvariant());

	RECT clientRectangle;
	GetClientRect(fWindowHandle, &clientRectangle);
	const int WINDOW_WIDTH = (clientRectangle.right - clientRectangle.left);
	VGCAssert(0 <= WINDOW_WIDTH);
	return WINDOW_WIDTH;
}

void VGCWindow::handleMessages(){
	VGCAssert(fInvariant());

	fHandleMessages();

	VGCAssert(fInvariant());
}

void VGCWindow::initializeWindow(const std::string &title, int width, int height){
	VGCAssert(0 <= width);
	VGCAssert(0 <= height);

	if(0 == fInitializeMinusFinalizeCount){
		VGCBus::initializeBus();

		WNDCLASSEX windowClass;
		windowClass.cbSize          = sizeof(WNDCLASSEX); 
		windowClass.style           = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc	    = (WNDPROC)fWindowCallback;
		windowClass.cbClsExtra      = 0;
		windowClass.cbWndExtra      = 0;
		windowClass.hInstance       = GetModuleHandle(NULL);
		windowClass.hIcon           = LoadIcon(NULL, IDI_WINLOGO);
		windowClass.hCursor		    = LoadCursor(NULL, IDC_ARROW);
		windowClass.hbrBackground   = NULL;
		windowClass.lpszMenuName    = NULL;
		windowClass.lpszClassName   = fWindowClassName;
		windowClass.hIconSm         = NULL;
		ATOM windowClassIdentifier  = RegisterClassEx(&windowClass);
		VGCAssert((0 != windowClassIdentifier) && "Window class created successfully.");

		fWindowHandle = CreateWindow(
			fWindowClassName, 
			title.c_str(), 
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
			CW_USEDEFAULT, 
			0, 
			width, 
			height, 
			NULL, 
			NULL, 
			GetModuleHandle(NULL), 
			NULL
		);
		VGCAssert((NULL != fWindowHandle) && "Window created successfully.");

		fSetWindowClientSize(fWindowHandle, width, height);
		ShowWindow(fWindowHandle, SW_SHOW);
		UpdateWindow(fWindowHandle);

		fWindowIsOpen = true;
	}
	fInitializeMinusFinalizeCount++;

	VGCAssert(fInvariant());
}

bool VGCWindow::windowIsOpen(){
	VGCAssert(fInvariant());

	return fWindowIsOpen;
}

