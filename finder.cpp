Mat finder(Mat img, string cass)
{
	
	resize(img, img, Size(600, 400));
	// Load cascate classifier placed in sulution folder
	CascadeClassifier detector;
	string cascadeName = cass;
	bool loaded = detector.load(cascadeName);
	// Parameters of detectMultiscale Cascade Classifier
	int groundThreshold = 2;
	double scaleStep = 1.1;
	Size minimalObjectSize(100, 100);
	Size maximalObjectSize(200, 200);
	// Vector of returned found
	vector<Rect> found;
	// Convert input to greyscale 
	Mat image_grey;
	cvtColor(img, image_grey, CV_BGR2GRAY);
	// why not
	found.clear();
	// Detect found
	detector.detectMultiScale(image_grey, found, scaleStep, groundThreshold, 0 | 2, minimalObjectSize, maximalObjectSize);
	// Draw circles on the detected found
	for (int i = 0; i < found.size(); i++)
	{
		Point pt1(found[i].x, found[i].y); // Display detected faces on main window - live stream from camera
		Point pt2((found[i].x + found[i].height), (found[i].y + found[i].width));
		rectangle(img, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
				
	}
	
	
	return img;
	
	
}