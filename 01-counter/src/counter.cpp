#include "counter.h"

void counter::do_count() {

	if (reset.read() == 1) {
		count = 0;
		cnt_out.write(count);
		ovf_intr.write(0);
		unf_intr.write(0);

	} else if (count_en.read() == 1) {
		// Increment
		if (ud_ctrl.read() == 1) {
			count = count + 1;

			if (count == 0) {
				ovf_intr.write(1);
			}
			else{
				ovf_intr.write(0);
			}

			cnt_out.write(count);
		}
		// Decrement
		else if (ud_ctrl.read() == 0) {

			if (count == 0) {
				unf_intr.write(1);
			}else{
				unf_intr.write(0);
			}

			count = count - 1;
			cnt_out.write(count);
		}
	}
}

