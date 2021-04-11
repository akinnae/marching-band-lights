// Return the integer address of location i for Strip A.
//    Because this is the first strip, it simply returns the input
//    value (e.g., location 5 on Strip A is the 5th pixel. Keep in
//    mind indexing from 1 vs 0. We go from 0.). 
int STRIP_A(int i){
  return i;
}

// Return the integer address of location i for Strip B.
//    For the second strip, it is in a visually-reversed direction.
//    So, we decrement from the final pin rather than incrementing
//    from the first. E.g. location 5 on Strip B is the 5th pixel
//    from the end of B: 59-5, the 54th pixel.
int STRIP_B(int i){
  return 59-i;
}

// Return the integer address of location i for Strip C.
//    For the third strip, it's in the same direction as the first,
//    so we increment from the beginning of the strip. Thus, 
//    location 5 on Strip C is the 5th pixel from the beginning
//    of C: 60+5, the 65th pixel.
int STRIP_C(int i){
  return 60+i;
}
