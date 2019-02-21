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
#include "ObjectDetectionView.h"
#include "../Evision3dViz/Evision3dViz.h"
#include "StereoMatcherView.h"
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


	logView =LogView::getInstance();
	logView->show();

	old_pos = this->pos();
	old_size = this->size();
	logView->move(*new QPoint(old_pos.x() + 10 + this->frameGeometry().width(), old_pos.y()));
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
	Evision3dViz  * evision3dViz = new Evision3dViz();
	ui.mdiArea->addSubWindow(evision3dViz);
	evision3dViz->show();
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
//����Ŀ������ͼ
void EvisionView::on_action_ObjectDetection_view()
{
	ObjectDetectionView* _ObjectDetectionView = new ObjectDetectionView();
	ui.mdiArea->addSubWindow(_ObjectDetectionView);
	_ObjectDetectionView->show();
}

//���Է���
void EvisionView::onTestAlltheParam()
{
	//printf("From printf ... ");
	//fflush(stdout);
	//fprintf(stderr, "From fprintf...");
	//std::cout << "From std::cout..." << std::endl;
	//std::cerr << "From std::cerr..." << std::endl;
	//qDebug() << "From qDebug ..." << QDateTime::currentDateTime().toString();	   
	//StereoMatcherView * _StereoMatcherView = new StereoMatcherView();
	//ui.mdiArea->addSubWindow(_StereoMatcherView);
	//_StereoMatcherView->show();
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
//�����ƶ��¼�
void EvisionView::moveEvent(QMoveEvent* event)
{
	//QWidget::moveEvent(event);
	QPoint delta = this->pos() - old_pos;
	//��������ڵ��ƶ���
	//�Ӵ��ڽ��е����ƶ�
	logView->move(delta + *new QPoint(old_pos.x() + 10 + this->frameGeometry().width(), old_pos.y()));
	old_pos = this->pos();
}

void EvisionView::resizeEvent(QResizeEvent* event)
{
	if (this->size().width() != old_size.width())
	{
		logView->move(*new QPoint(old_pos.x() + 10 + this->frameGeometry().width(), old_pos.y()));
		old_size = this->size();
	}
}

void EvisionView::changeEvent(QEvent*event)
{
	if (event->type() != QEvent::WindowStateChange) return;
	if (this->windowState() == Qt::WindowMaximized)//���
	{
		//logView->setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
	}
	if (this->windowState() == Qt::WindowMinimized)//��С��
	{
		//logView->setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint);

	}
}

void EvisionView::closeEvent(QCloseEvent* event)
{
	logView->close();
}

