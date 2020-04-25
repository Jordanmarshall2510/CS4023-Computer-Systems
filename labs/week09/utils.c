int approxEqual(float matrix, float ref, float tol ){
	return((matrix >= ref-tol) && (matrix <= ref+tol));
}
