#include "VGCMessage.h"
#include "VGCAssert.h"
#include "VGCReferenced.h"
#include "VGCKey.h"



/* VGCMessage */

/* Public creators */
VGCMessage::VGCMessage() :
	VGCReferenced(){

	VGCAssert(invariant());
}

VGCMessage::VGCMessage(const VGCMessage &message) :
	VGCReferenced(){
	
	VGCAssert(invariant());
}

VGCMessage::~VGCMessage(){
	VGCAssert(invariant());
}

/* Protected accessors */
bool VGCMessage::invariant() const{
	return VGCReferenced::invariant();
}


/* VGCNotificationMessage */

/* Public creators */
VGCNotificationMessage::VGCNotificationMessage(Notification notification) :
	VGCMessage(),
	mNotification(notification){
	
	VGCAssert(invariant());
}

VGCNotificationMessage::VGCNotificationMessage(const VGCNotificationMessage &notificationMessage) :
	VGCMessage(),
	mNotification(notificationMessage.mNotification){
	
	VGCAssert(invariant());
}

VGCNotificationMessage::~VGCNotificationMessage(){
	VGCAssert(invariant());

	mNotification = MIN_NOTIFICATION;

	VGCAssert(!invariant());
}

/* Public manipulators */
void VGCNotificationMessage::setNotification(Notification notification){
	VGCAssert(invariant());

	mNotification = notification;

	VGCAssert(invariant());
}

/* Public accessors */
VGCMessage* VGCNotificationMessage::clone() const{
	VGCAssert(invariant());

	VGCMessage *clone = new VGCNotificationMessage(*this);
	VGCAssert(clone);
	return clone;
}

VGCNotificationMessage::Notification VGCNotificationMessage::getNotification() const{
	VGCAssert(invariant());

	return mNotification;
}

/* Protected accessors */
bool VGCNotificationMessage::invariant() const{
	return 
		(VGCMessage::invariant()) && 
		(MIN_NOTIFICATION < mNotification) &&
		(mNotification < MAX_NOTIFICATION);
}



/* VGCCharacterMessage */

/* Public creators */
VGCCharacterMessage::VGCCharacterMessage(char character) :
	VGCMessage(),
	mCharacter(character){
	
	VGCAssert(invariant());
}	

VGCCharacterMessage::VGCCharacterMessage(const VGCCharacterMessage &characterMessage) :
	VGCMessage(),
	mCharacter(characterMessage.mCharacter){
	
	VGCAssert(invariant());
}

VGCCharacterMessage::~VGCCharacterMessage(){
	VGCAssert(invariant());
}

/* Public manipulators */
void VGCCharacterMessage::setCharacter(char character){
	VGCAssert(invariant());

	mCharacter = character;

	VGCAssert(invariant());
}

/* Public accessors */
VGCMessage* VGCCharacterMessage::clone() const{
	VGCAssert(invariant());

	VGCMessage *clone = new VGCCharacterMessage(*this);
	VGCAssert(clone);
	return clone;
}

char VGCCharacterMessage::getCharacter() const{
	VGCAssert(invariant());

	return mCharacter;
}

/* Protected accessors */
bool VGCCharacterMessage::invariant() const{
	return VGCMessage::invariant();
}



/* VGCKeyMessage */

/* Public creators */
VGCKeyMessage::VGCKeyMessage(Event event, const VGCKey key) :
	VGCMessage(),
	mEvent(event),
	mKey(key){

	VGCAssert(invariant());
}

VGCKeyMessage::VGCKeyMessage(const VGCKeyMessage &keyMessage) :
	VGCMessage(),
	mEvent(keyMessage.mEvent),
	mKey(keyMessage.mKey){

	VGCAssert(invariant());
}

VGCKeyMessage::~VGCKeyMessage(){
	VGCAssert(invariant());
}

/* Public manipulators */
void VGCKeyMessage::setEvent(Event event){
	VGCAssert(invariant());

	mEvent = event;

	VGCAssert(invariant());
}

void VGCKeyMessage::setKey(const VGCKey &key){
	VGCAssert(invariant());

	mKey = key;

	VGCAssert(invariant());
}

/* Public accessors */
VGCMessage* VGCKeyMessage::clone() const{
	VGCAssert(invariant());

	VGCMessage *clone = new VGCKeyMessage(*this);
	VGCAssert(clone);
	return clone;
}

VGCKeyMessage::Event VGCKeyMessage::getEvent() const{
	VGCAssert(invariant());

	return mEvent;
}

const VGCKey& VGCKeyMessage::getKey() const{
	VGCAssert(invariant());

	return mKey;
}

/* Protected accessors */
bool VGCKeyMessage::invariant() const{
	return 
		VGCMessage::invariant() &&
		(MIN_EVENT < mEvent) &&
		(mEvent < MAX_EVENT);
}
