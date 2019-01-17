#include "EvisionView.h"
#include "QDebug"
#include "QMessageBox"
#include "EvisionUtils.h"
#include "Calibrater.h"
#include "Matcher.h"
#include <qevent.h>
#include <qmimedata.h>
#include <QFileDialog>
#include "RFinterface.h"
#include "StereoCamera.h"
#include "Camera.h"
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
	Camera * _camera = new Camera();
	ui.mdiArea->addSubWindow(_camera);
	_camera->show();
}
//��ʾ˫Ŀ�����ͼ
void EvisionView::onStereoCamera()
{
	StereoCamera * _stereoCamera = new StereoCamera();
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
		cv::Mat xyz = StereoMatch::readXYZ(xyzFile.toStdString().c_str());
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
	Calibrater * m_calibrate = new Calibrater();
	ui.mdiArea->addSubWindow(m_calibrate);
	m_calibrate->show();
}
//��ʾ����ƥ����ͼ
void EvisionView::on_action_stereoMatch_view()
{
	Matcher * m_matcher = new Matcher();
	ui.mdiArea->addSubWindow(m_matcher);
	m_matcher->show();
}
//��ʾ����ʽ�����ͼ
void EvisionView::on_action_Measure_view()
{
	cv::Mat img, disp, xyz;

	//ѯ���ļ�λ�ò��������
	QString imgFile, dispFile, xyzFile;
	QFileDialog * fileDialog = new QFileDialog();
	fileDialog->setWindowTitle(QStringLiteral("��ѡ���Ӳ�ͼ"));
	fileDialog->setNameFilter(QStringLiteral("ͼƬ�ļ�(*.jpg *.png *.jpeg)"));
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	if (fileDialog->exec() == QDialog::Accepted)
	{
		imgFile = fileDialog->selectedFiles().at(0);
		fileDialog->setWindowTitle(QStringLiteral("��ѡ�����������ѡ�Ӳ�ͼ������ͼ"));
		if (fileDialog->exec() == QDialog::Accepted)
		{
			dispFile = fileDialog->selectedFiles().at(0);

			QFileDialog * fileDialog2 = new QFileDialog();
			fileDialog2->setWindowTitle(QStringLiteral("��ѡ������ļ�"));
			fileDialog2->setNameFilter(QStringLiteral("�����ļ�(*.xml *.yml *.yaml)"));
			fileDialog2->setFileMode(QFileDialog::ExistingFile);
			if (fileDialog2->exec() == QDialog::Accepted)
			{
				xyzFile = fileDialog2->selectedFiles().at(0);
				if (imgFile.isEmpty() || dispFile.isEmpty() || xyzFile.isEmpty())
				{
					//�ļ���ȫ,������ʾ�˳�
					QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
					return;
				}
				else
				{
					//�ļ���ȫ,��ȡ����
					img = cv::imread(imgFile.toStdString());
					disp = cv::imread(dispFile.toStdString());
					xyz = StereoMatch::readXYZ(xyzFile.toStdString().c_str());
				}
			}
			else
			{
				QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
				return;
			}
		}
		else
		{
			QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
			return;
		}
	}
	else
	{
		QMessageBox::information(NULL, QStringLiteral("����"), QStringLiteral("��ѡ����Ч���ļ�!"));
		return;
	}


	//׼����������,����������е����λ��,˵������������ֵ��������Чֵ,��ʱ������������ʽ������view
	//img,disp.xyz
	RFinterface * _Rfinterface = new RFinterface(img, disp, xyz);
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
		QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("����һ���ļ�"));
	}else if(urls.size()==1)
	{
		QMessageBox::information(NULL, QStringLiteral("��Ϣ"), QStringLiteral("һ���ļ�"));
		//�ļ�����ʶ��ʹ�
		QFileInfo fileinfo(urls[0].toString());
		if (!fileinfo.isFile())//�����ļ�
		{
			return;
		}
		else
		{
			if (fileinfo.suffix() == "png"|| fileinfo.suffix() == "jpg"||
				fileinfo.suffix() == "jpeg")
			{
				
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

