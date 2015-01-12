#include <QtCore>
#include <QtNetwork>

//���߳����ص��߳���
const int PointCount = 5;
//Ŀ���ļ��ĵ�ַ��ǧǧ���������ص�ַ����������ʵ��ģ�
const QString strUrl = "http://ttplayer.qianqian.com/otherdown/alladin/ttpsetup_5713.exe";

//���������ļ������ļ���һ���֣�
class MultiThreadHttpTask : public QObject
{
	Q_OBJECT
private:
	QNetworkAccessManager m_Qnam;
	QNetworkReply *m_Reply;
	QFile *m_File;

	const int m_Index;
	qint64 m_HaveDoneBytes;
	qint64 m_StartPoint;
	qint64 m_EndPoint;

public:
	MultiThreadHttpTask(int index, QObject *parent = 0);
	void StartDownload(const QUrl &url, QFile *file,
		qint64 startPoint = 0, qint64 endPoint = -1);
signals:
	void DownloadFinished();

	public slots:
	void FinishedSlot();
	void HttpReadyRead();
};

//���ڹ����ļ�������
class DownloadControl : public QObject
{
	Q_OBJECT
private:
	int m_DownloadCount;
	int m_FinishedNum;
	int m_FileSize;
	QUrl m_Url;
	QFile *m_File;
public:
	DownloadControl(QObject *parent = 0);
	void StartFileDownload(const QString &url, int count);
	qint64 GetFileSize(QUrl url);
signals:
	void FileDownloadFinished();
	private slots:
	void SubPartFinished();
};

MultiThreadHttpTask::MultiThreadHttpTask(int index, QObject *parent)
	: QObject(parent), m_Index(index)
{
	m_HaveDoneBytes = 0;
	m_StartPoint = 0;
	m_EndPoint = 0;
	m_File = NULL;
}

void MultiThreadHttpTask::StartDownload(const QUrl &url,
	QFile *file,
	qint64 startPoint/* =0 */,
	qint64 endPoint/* =-1 */)
{
	if (NULL == file)
		return;

	m_HaveDoneBytes = 0;
	m_StartPoint = startPoint;
	m_EndPoint = endPoint;
	m_File = file;

	//����HTTPЭ�飬д��RANGEͷ����˵�������ļ��ķ�Χ
	QNetworkRequest qheader;
	qheader.setUrl(url);
	QString range;
	range.sprintf("Bytes=%lld-%lld", m_StartPoint, m_EndPoint);
	qheader.setRawHeader("Range", range.toLocal8Bit());// .toAscii());

	//��ʼ����
	qDebug() << "Part " << m_Index << " start download";
	m_Reply = m_Qnam.get(QNetworkRequest(qheader));
	connect(m_Reply, SIGNAL(finished()),
		this, SLOT(FinishedSlot()));
	connect(m_Reply, SIGNAL(readyRead()),
		this, SLOT(HttpReadyRead()));
}

//���ؽ���
void MultiThreadHttpTask::FinishedSlot()
{
	m_File->flush();
	m_Reply->deleteLater();
	m_Reply = 0;
	m_File = 0;
	qDebug() << "Part " << m_Index << " download finished";
	emit DownloadFinished();
}

void MultiThreadHttpTask::HttpReadyRead()
{
	if (!m_File)
		return;

	//����������Ϣд���ļ�
	QByteArray buffer = m_Reply->readAll();
	m_File->seek(m_StartPoint + m_HaveDoneBytes);
	m_File->write(buffer);
	m_HaveDoneBytes += buffer.size();
}

//�������ķ�ʽ��ȡ�����ļ��ĳ���
qint64 DownloadControl::GetFileSize(QUrl url)
{
	QNetworkAccessManager manager;
	qDebug() << "Getting the file size...";
	QEventLoop loop;
	//�������󣬻�ȡĿ���ַ��ͷ����Ϣ
	QNetworkReply *reply = manager.head(QNetworkRequest(url));
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()), Qt::DirectConnection);
	loop.exec();
	QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
	delete reply;
	qint64 size = var.toLongLong();
	qDebug() << "The file size is: " << size;
	return size;
}

DownloadControl::DownloadControl(QObject *parent)
	: QObject(parent)
{
	m_DownloadCount = 0;
	m_FinishedNum = 0;
	m_FileSize = 0;
	m_File = new QFile;
}

void DownloadControl::StartFileDownload(const QString &url, int count)
{
	m_DownloadCount = count;
	m_FinishedNum = 0;
	m_Url = QUrl(url);
	m_FileSize = GetFileSize(m_Url);
	//�Ȼ���ļ�������
	QFileInfo fileInfo(m_Url.path());
	QString fileName = fileInfo.fileName();
	if (fileName.isEmpty())
		fileName = "index.html";

	m_File->setFileName(fileName);
	//���ļ�
	m_File->open(QIODevice::WriteOnly);
	MultiThreadHttpTask *tempDownload;

	//���ļ��ֳ�PointCount�Σ����첽�ķ�ʽ����
	qDebug() << "Start download file from " << strUrl;
	for (int i = 0; i<m_DownloadCount; i++)
	{
		//�����ÿ�εĿ�ͷ�ͽ�β��HTTPЭ������Ҫ����Ϣ��
		int start = m_FileSize * i / m_DownloadCount;
		int end = m_FileSize * (i + 1) / m_DownloadCount;
		if (i != 0)
			start--;

		//�ֶ����ظ��ļ�
		tempDownload = new MultiThreadHttpTask(i + 1, this);
		connect(tempDownload, SIGNAL(DownloadFinished()),
			this, SLOT(SubPartFinished()));
		connect(tempDownload, SIGNAL(DownloadFinished()),
			tempDownload, SLOT(deleteLater()));
		tempDownload->StartDownload(m_Url, m_File, start, end);
	}
}

void DownloadControl::SubPartFinished()
{
	m_FinishedNum++;
	//�������������ļ���������˵���ļ�������ϣ��ر��ļ��������ź�
	if (m_FinishedNum == m_DownloadCount)
	{
		m_File->close();
		emit FileDownloadFinished();
		qDebug() << "Download finished";
	}
}

//#include "main.moc"
//
//int main(int argc, char **argv)
//{
//	QCoreApplication app(argc, argv);
//	//�������ķ�ʽ�����ļ�����ɺ��˳�
//	DownloadControl *control = new DownloadControl;
//	QEventLoop loop;
//	QObject::connect(control, SIGNAL(FileDownloadFinished()),
//		&loop, SLOT(quit()));
//	control->StartFileDownload(strUrl, PointCount);
//	loop.exec();
//	return 0;
//}