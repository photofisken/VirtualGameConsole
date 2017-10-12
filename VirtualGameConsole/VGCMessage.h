#ifndef INCLUDED_VGCMESSAGE
#define INCLUDED_VGCMESSAGE



/******************************************************************************

This component implements message types used to notify clients about events
such as key presses/releases.

*******************************************************************************/



#include "VGCReferenced.h"
#include "VGCKey.h"



class VGCMessage : public VGCReferenced{
public:

	/* Public creators */
	VGCMessage();
	VGCMessage(const VGCMessage &message);
	virtual ~VGCMessage();

	/* Public accessors */
	virtual VGCMessage* clone() const = 0;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCMessage& operator=(const VGCMessage &message);
};



class VGCNotificationMessage : public VGCMessage{
public:

	/* Public types */
	enum Notification{
		MIN_NOTIFICATION = 1,
		NULL_NOTIFICATION,
		PAINT_NOTIFICATION,
		MAX_NOTIFICATION,
	};

	/* Public creators */
	VGCNotificationMessage(Notification notification = NULL_NOTIFICATION);
	VGCNotificationMessage(const VGCNotificationMessage &notificationMessage);
	virtual ~VGCNotificationMessage();

	/* Public manipulators */
	void setNotification(Notification notification);

	/* Public accessors */
	virtual VGCMessage* clone()           const;
	Notification        getNotification() const;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCNotificationMessage& operator=(const VGCNotificationMessage &notificationMessage);

	/* Private data */
	Notification mNotification;
};



class VGCCharacterMessage : public VGCMessage{
public:

	/* Public creators */
	VGCCharacterMessage(char character = '\0');
	VGCCharacterMessage(const VGCCharacterMessage &characterMessage);
	virtual ~VGCCharacterMessage();

	/* Public manipulators */
	void setCharacter(char character);

	/* Public accessors */
	virtual VGCMessage* clone()        const;
	char                getCharacter() const;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCCharacterMessage& operator=(const VGCCharacterMessage &characterMessage);

	/* Private data */
	char mCharacter;
};



class VGCKeyMessage : public VGCMessage{
public:

	/* Public types */
	enum Event{
		MIN_EVENT = 1,
		PRESS_EVENT,
		RELEASE_EVENT,
		MAX_EVENT
	};

	/* Public creators */
	VGCKeyMessage(Event event = PRESS_EVENT, const VGCKey key = VGCKey());
	VGCKeyMessage(const VGCKeyMessage &keyMessage);
	virtual ~VGCKeyMessage();

	/* Public manipulators */
	void setEvent(Event event);
	void setKey(const VGCKey &key);

	/* Public accessors */
	virtual VGCMessage* clone()    const;
	Event               getEvent() const;
	const VGCKey&       getKey()   const;

protected:

	/* Protected accessors */
	bool invariant() const;

private:

	/* Private manipulators */
	VGCKeyMessage& operator=(const VGCKeyMessage &keyMessage);

	/* Private data */
	Event  mEvent;
	VGCKey mKey;
};


#endif