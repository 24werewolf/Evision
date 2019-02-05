#include "EvisionView.h"
#include "QDebug"
#include "QMessageBox"
#include "EvisionUtils.h"
#include "CalibraterView.h"
#include "MatcherView.h"
#include <qevent.h>
#include <qmimedata.h>
#include <QFileDialog>
#include "RulerView.h"
#include "StereoCameraView.h"
#include "CameraView.h"
#include "WatchImageView.h"
// �������е�
// ulp: units in the last place.
template <typename T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
IsAlmostEqual(T x, T y, int ulp = 2)
{
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place)
	return std::abs(x - y) < std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}

//���캯��
EvisionView::EvisionView(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setAcceptDrops(true);
	msgLabel = new QLabel;
	msgLabel->setMinimumSize(msgLabel->sizeHint());
	msgLabel->setAlignment(Qt::AlignHCenter);
	msgLabel->setText(QStringLiteral("����"));
	statusBar()->addWidget(msgLabel);
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

	m_entity = EvisionParamEntity::getInstance();
	m_controller = new EvisionController();


	connect(m_entity, SIGNAL(paramChanged_StatusBar()), this, SLOT(onParamChanged_StatusBarText()), Qt::QueuedConnection);

}


//��ʾ��Ŀ�����ͼ
void EvisionView::onCamera()
{
	CameraView * _camera = new CameraView();
	ui.mdiArea->addSubWindow(_camera);
	_camera->show();
}
//��ʾ˫Ŀ�����ͼ
void EvisionView::onStereoCamera()
{
	StereoCameraView * _stereoCamera = new StereoCameraView();
	ui.mdiArea->addSubWindow(_stereoCamera);
	_stereoCamera->show();
}

//��ʾ����
void EvisionView::onShowPointCloud()
{
	//TODO:need refactor
	QFileDialog * fileDialog2 = new QFileDialog();
	fileDialog2->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
	fileDialog2->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
	fileDialog2->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog2->exec() == QDialog::Accepted)
	{
		QString xyzFile = fileDialog2->selectedFiles().at(0);
		cv::Mat xyz;
		if (EvisionUtils::read_PointCloud(xyzFile.toStdString(), &xyz))
		{
		}
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч�ĵ����ļ�!"));
		return;
	}
	//���ƻ�ȡok,׼����ʾ
}
//��ʾ�궨��ͼ
void EvisionView::on_action_calibrate_view()
{
	CalibraterView * m_calibrate = new CalibraterView();
	ui.mdiArea->addSubWindow(m_calibrate);
	m_calibrate->show();
}
//��ʾ����ƥ����ͼ
void EvisionView::on_action_stereoMatch_view()
{
	MatcherView * m_matcher = new MatcherView();
	ui.mdiArea->addSubWindow(m_matcher);
	m_matcher->show();
}
//��ʾ����ʽ�����ͼ
void EvisionView::on_action_Measure_view()
{
	RulerView * _Rfinterface = new RulerView();
	ui.mdiArea->addSubWindow(_Rfinterface);
	_Rfinterface->show();
}

//���Է���
void EvisionView::onTestAlltheParam()
{

}
//״̬������
void EvisionView::onParamChanged_StatusBarText()
{
	msgLabel->setText(m_entity->getStatusBarText());
}
//�ļ����ϵ�����������
void EvisionView::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
	{
		event->acceptProposedAction();
		//QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("�ļ���������"));
		m_entity->setStatusBarText("Drop the file for open!");
	}
}
//�ļ��ڴ��������ϱ�����
void EvisionView::dropEvent(QDropEvent * event)
{
	m_entity->setStatusBarText(QStringLiteral("����"));
	//QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("�ļ����ͷ��ڴ�����"));
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
	{
		return;
	}
	else if(urls.size()>1)
	{
		//QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("����һ���ļ�"));
	}else if(urls.size()==1)
	{
		//QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("һ���ļ�"));
		//�ļ�����ʶ��ʹ�
		QString file_name = urls[0].toLocalFile();
		QFileInfo fileinfo(file_name);
		if (!fileinfo.isFile())//�����ļ�
		{
			return;
		}
		else
		{
			if (fileinfo.suffix() == "png"|| fileinfo.suffix() == "jpg"||
				fileinfo.suffix() == "jpeg")
			{
				WatchImageView * m_WatchImage = new WatchImageView(file_name);
				ui.mdiArea->addSubWindow(m_WatchImage);
				m_WatchImage->show();
			}
		}
	}
		
}
//����ͷ��¼�
void EvisionView::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_entity->setStatusBarText(QStringLiteral("����"));
	}
}

