#include <QImage>

QPixmap get_blurred_image_tweak(QString url)
{
	QPixmap inPixmap(url);

	QLabel* label = new QLabel();
	label->setPixmap(inPixmap);
	label->setGraphicsEffect(new QGraphicsBlurEffect());
	QPixmap output(inPixmap.width(), inPixmap.height());
	QPainter painter(&output);
	label->render(&painter);
	return output;
}

QImage * get_blurred_image(QImage * origin)
{
	QImage * newImage = new QImage(*origin);

	int kernel[5][5] = { 
    { 0, 0, 1, 0, 0 },
	{ 0, 1, 3, 1, 0 },
	{ 1, 3, 7, 3, 1 },
	{ 0, 1, 3, 1, 0 },
	{ 0, 0, 1, 0, 0 } };
	int kernelSize = 5;
	int sumKernel = 27;
	int r, g, b;
	QColor color;

	for (int x = kernelSize / 2; x<newImage->width() - (kernelSize / 2); x++)
	{
		for (int y = kernelSize / 2; y<newImage->height() - (kernelSize / 2); y++)
		{

			r = 0;
			g = 0;
			b = 0;

			for (int i = -kernelSize / 2; i <= kernelSize / 2; i++){
				for (int j = -kernelSize / 2; j <= kernelSize / 2; j++){
					color = QColor(origin->pixel(x + i, y + j));
					r += color.red()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					g += color.green()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
					b += color.blue()*kernel[kernelSize / 2 + i][kernelSize / 2 + j];
				}
			}

			r = qBound(0, r / sumKernel, 255);
			g = qBound(0, g / sumKernel, 255);
			b = qBound(0, b / sumKernel, 255);

			newImage->setPixel(x, y, qRgb(r, g, b));

		}
	}
	return newImage;
}

QImage *get_blurred_image(const QImage& image, const QRect& rect, int radius, bool alphaOnly)
{
	int *tab = new int[100];
	for (int i = 0; i <= 100; ++i)
	{
		tab[i] = i;
	}

	//int tab[] = { 14, 10, 8, 6, 5, 5, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2 };
	//int alpha = (radius < 1) ? 16 : (radius > 17) ? 1 : tab[radius - 1];
	int alpha = (radius < 0) ? 16 : (radius > 100) ? 1 : tab[radius - 1];

	QImage *result = new QImage(image.convertToFormat(QImage::Format_ARGB32_Premultiplied));
	int r1 = rect.top();
	int r2 = rect.bottom();
	int c1 = rect.left();
	int c2 = rect.right();

	int bpl = result->bytesPerLine();
	int rgba[4];
	unsigned char* p;

	int i1 = 0;
	int i2 = 3;

	if (alphaOnly)
		i1 = i2 = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

	for (int col = c1; col <= c2; col++) {
		p = result->scanLine(r1) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += bpl;
		for (int j = r1; j < r2; j++, p += bpl)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result->scanLine(row) + c1 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p += 4;
		for (int j = c1; j < c2; j++, p += 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int col = c1; col <= c2; col++) {
		p = result->scanLine(r2) + col * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= bpl;
		for (int j = r1; j < r2; j++, p -= bpl)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	for (int row = r1; row <= r2; row++) {
		p = result->scanLine(row) + c2 * 4;
		for (int i = i1; i <= i2; i++)
			rgba[i] = p[i] << 4;

		p -= 4;
		for (int j = c1; j < c2; j++, p -= 4)
			for (int i = i1; i <= i2; i++)
				p[i] = (rgba[i] += ((p[i] << 4) - rgba[i]) * alpha / 16) >> 4;
	}

	return result;
}