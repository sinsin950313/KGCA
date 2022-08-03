#include "CustomRBTree.h"

int main()
{
	RBTree rb;
	rb.insert(1);
	rb.insert(2);
	rb.insert(3);
	rb.insert(4);
	rb.insert(5);
	rb.insert(6);
	rb.insert(7);
	rb.insert(8);
	rb.insert(9);

	//rb.Erase(rb.Find(4));
	//rb.Erase(rb.Find(5));
	//rb.Erase(rb.Find(6));
	//rb.Erase(rb.Find(7));

	RBTree rbr;
	rbr.insert(9);
	rbr.insert(8);
	rbr.insert(7);
	rbr.insert(6);
	rbr.insert(5);
	rbr.insert(4);
	rbr.insert(3);
	rbr.insert(2);
	rbr.insert(1);
}