class QuestionTwo {
    
    // this function takes 1 millisecond to run
    void f_1ms () {
	// unknown implementation
    }
    
    // this function takes 3 milliseconds to run
    void f_3ms () {
	// unknown implementation
    }
    
    
    void question_2a (int N) {
	for (int ii = 0; ii < N; ii += 3) {
	    f_3ms ();
	    for (int jj = 0; jj < N; ++jj) {
		f_1ms ();
	    }
	}
    }
    
    
    void question_2b (int N) {
	for (int ii = 0; ii < N; ++ii) {
	    f_3ms ();
	}
	for (int jj = 0; jj < N; jj += 2) {
	    f_1ms ();
	}
    }
    
    
    void helper_2c (int N) {
	if (N <= 1) {
	    f_3ms ();
	}
	else {
	    helper_2c (N / 2);
	}
    }
    
    void question_2c (int N) {
	for (int ii = 0; ii < N; ++ii) {
	    f_1ms ();
	    helper_2c (N);
	}
    }
    
    
    void question_2d (int N) {
	for (int ii = 1; ii < N; ii *= 2) {
	    f_3ms ();
	    for (int jj = 0; jj < N; ++jj) {
		f_1ms();
	    }
	}
    }

}
