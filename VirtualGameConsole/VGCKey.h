#ifndef INCLUDED_VGCKEY
#define INCLUDED_VGCKEY



/******************************************************************************

This component implements a type used to represent typical keys on a keyboard.

*******************************************************************************/



#include "VGCAssert.h"



class VGCKey{
public:

	/* Public types */
	enum Key{
		MIN_KEY = 1,
		NULL_KEY,
		BACKSPACE_KEY,
		TAB_KEY,
		RETURN_KEY,
		SHIFT_KEY,
		CONTROL_KEY,
		MENU_KEY,
		ESCAPE_KEY,
		SPACE_KEY,
		PAGE_UP_KEY,
		PAGE_DOWN_KEY,
		END_KEY,
		HOME_KEY,
		ARROW_LEFT_KEY,
		ARROW_UP_KEY,
		ARROW_RIGHT_KEY,
		ARROW_DOWN_KEY,
		DELETE_KEY,
		ZERO_KEY,
		ONE_KEY,
		TWO_KEY,
		THREE_KEY,
		FOUR_KEY,
		FIVE_KEY,
		SIX_KEY,
		SEVEN_KEY,
		EIGHT_KEY,
		NINE_KEY,
		A_KEY,
		B_KEY,
		C_KEY,
		D_KEY,
		E_KEY,
		F_KEY,
		G_KEY,
		H_KEY,
		I_KEY,
		J_KEY,
		K_KEY,
		L_KEY,
		M_KEY,
		N_KEY,
		O_KEY,
		P_KEY,
		Q_KEY,
		R_KEY,
		S_KEY,
		T_KEY,
		U_KEY,
		V_KEY,
		W_KEY,
		X_KEY,
		Y_KEY,
		Z_KEY,
		PAD_ZERO_KEY,
		PAD_ONE_KEY,
		PAD_TWO_KEY,
		PAD_THREE_KEY,
		PAD_FOUR_KEY,
		PAD_FIVE_KEY,
		PAD_SIX_KEY,
		PAD_SEVEN_KEY,
		PAD_EIGHT_KEY,
		PAD_NINE_KEY,
		PAD_MULTIPLY_KEY,
		PAD_ADD_KEY,
		PAD_SUBTRACT_KEY,
		PAD_DIVIDE_KEY,
		F1_KEY,
		F2_KEY,
		F3_KEY,
		F4_KEY,
		F5_KEY,
		F6_KEY,
		F7_KEY,
		F8_KEY,
		F9_KEY,
		F10_KEY,
		F11_KEY,
		F12_KEY,
		MAX_KEY
	};

	/* Public creators */
	VGCKey(Key key = NULL_KEY) :
		mKey(key){
		
		VGCAssert(invariant());		
	}

	VGCKey(const VGCKey &key) :
	mKey(key.mKey){
	
		VGCAssert(invariant());		
	}

	~VGCKey(){
		VGCAssert(invariant());		
	
		mKey = MIN_KEY;

		VGCAssert(!invariant());		
	}

	/* Public manipualtors */
	VGCKey& operator=(const VGCKey &key){
		VGCAssert(invariant());		

		mKey = key.mKey;

		VGCAssert(invariant());	
		return *this;
	}

	void setKey(Key key){
		VGCAssert(invariant());		

		mKey = key;
	
		VGCAssert(invariant());		
	}

	/* Public accessors */
	Key getKey() const{
		VGCAssert(invariant());		

		return mKey;
	}

private:
	
	/* Private accessors */
	bool invariant() const{
		return ((MIN_KEY < mKey) && (mKey < MAX_KEY));	
	}

	/* Private data */
	Key mKey;
};

inline bool operator==(const VGCKey &key0, const VGCKey &key1){
	return (key0.getKey() == key1.getKey());
}

inline bool operator!=(const VGCKey &key0, const VGCKey &key1){
	return (key0.getKey() != key1.getKey());
}

inline bool operator<(const VGCKey &key0, const VGCKey &key1){
	return (key0.getKey() < key1.getKey());
}

#endif
