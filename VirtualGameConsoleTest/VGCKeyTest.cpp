#include "VGCKeyTest.h"
#include "VGCAssert.h"
#include "VGCKey.h"



/* VGCKeyTest */

/* Public functions */
void VGCKeyTest::run(){
	VGCKey k0;
	VGCAssert(VGCKey::NULL_KEY == k0.getKey());

	VGCKey k1(VGCKey::F1_KEY);
	VGCAssert(VGCKey::F1_KEY == k1.getKey());

	VGCKey k2(k1);
	VGCAssert(VGCKey::F1_KEY == k2.getKey());

	VGCKey k3;
	k3 = k2;
	VGCAssert(VGCKey::F1_KEY == k3.getKey());
	k3.setKey(VGCKey::F2_KEY);
	VGCAssert(VGCKey::F2_KEY == k3.getKey());

	VGCKey ka0(VGCKey::F1_KEY);
	VGCKey kb0(VGCKey::F2_KEY);
	VGCKey ka1(VGCKey::F1_KEY);
	VGCKey kb1(VGCKey::F2_KEY);
	VGCAssert(ka0 == ka1);
	VGCAssert(kb0 == kb1);
	VGCAssert(ka0 != kb0);
	VGCAssert(ka1 != kb1);
	VGCAssert(ka0 < kb0);
	VGCAssert(!(ka0 < ka0));
	VGCAssert(!(kb0 < ka0));
}

