#include "VGCMessageTest.h"
#include "VGCAssert.h"
#include "VGCMessage.h"



static void testVGCMessage(){
	/* Abstract baseclass, not tested for now...*/
}

static void testVGCNotificationMessage(){
	VGCNotificationMessage m0;
	VGCAssert(VGCNotificationMessage::NULL_NOTIFICATION == m0.getNotification());
	m0.setNotification(VGCNotificationMessage::NULL_NOTIFICATION);
	VGCAssert(VGCNotificationMessage::NULL_NOTIFICATION == m0.getNotification());

	VGCNotificationMessage m1(m0);
	VGCAssert(VGCNotificationMessage::NULL_NOTIFICATION == m1.getNotification());

	VGCMessage *clone = m1.clone();
	delete clone;
}

static void testVGCCharacterMessage(){
	VGCCharacterMessage m0;
	VGCAssert('\0' == m0.getCharacter());
	m0.setCharacter('a');
	VGCAssert('a' == m0.getCharacter());

	VGCCharacterMessage m1(m0);
	VGCAssert('a' == m1.getCharacter());
	
	VGCMessage *clone = m1.clone();
	delete clone;
}

static void testVGCKeyMessage(){
	VGCKeyMessage m0;
	VGCAssert(VGCKeyMessage::PRESS_EVENT == m0.getEvent());
	VGCAssert(VGCKey() == m0.getKey());
	m0.setEvent(VGCKeyMessage::RELEASE_EVENT);
	m0.setKey(VGCKey::F2_KEY);
	VGCAssert(VGCKeyMessage::RELEASE_EVENT == m0.getEvent());
	VGCAssert(VGCKey::F2_KEY == m0.getKey());
	VGCKeyMessage m1(m0);
	VGCAssert(VGCKeyMessage::RELEASE_EVENT == m1.getEvent());
	VGCAssert(VGCKey::F2_KEY == m1.getKey());

	VGCMessage *clone = m1.clone();
	delete clone;
}



/* VGCMessageTest */

/* Public functions */
void VGCMessageTest::run(){
	testVGCMessage();
	testVGCNotificationMessage();
	testVGCCharacterMessage();
	testVGCKeyMessage();
}

