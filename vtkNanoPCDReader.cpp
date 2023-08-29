#include "vtkNanoPCDReader.h"

#include <vtkObjectFactory.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>
#include <vtkPolyData.h>

#include <pcl/io/vtk_lib_io.h>
#include <pcl/io/pcd_io.h>

vtkStandardNewMacro(vtkNanoPCDReader);

vtkNanoPCDReader::vtkNanoPCDReader(void)
{
  this->FileName = NULL;
  this->SetNumberOfInputPorts(0);
}


vtkNanoPCDReader::~vtkNanoPCDReader(void)
{
  delete[] this->FileName;
}

void vtkNanoPCDReader::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os, indent);

	//os << indent << "Text: " << (this->Text ? this->Text : "(none)") << "\n";
	//os << indent << "FileName: " << (this->FileName ? this->FileName : "(none)") << "\n";
	os << indent << "FileName: " << this->FileName << "\n";
}

int vtkNanoPCDReader::RequestData(vtkInformation* vtkNotUsed(request), 
								  vtkInformationVector** input_vec, 
								  vtkInformationVector* output_vec)
{
	vtkInformation* out_info = output_vec->GetInformationObject(0);
	vtkPolyData* f_output = vtkPolyData::SafeDownCast(out_info->Get(vtkDataObject::DATA_OBJECT()));

	if( !this->FileName ) {
		vtkErrorMacro(<<"A File Name must be specified.");
		return 0;
	}

    pcl::PCLPointCloud2                         cloud2;
    pcl::PointCloud<pcl::PointXYZ>              cloud_xyz;
    pcl::PointCloud<pcl::PointXYZRGB>           cloud_rgb;
    pcl::PointCloud<pcl::PointNormal>           cloud_normal;
    pcl::PointCloud<pcl::PointXYZRGBNormal>     cloud_rgb_normal;
    bool                                        has_rgb = false;
    bool                                        has_normal = false;

	if( pcl::io::loadPCDFile(this->FileName, cloud2) >= 0 ) {
        std::string str = pcl::getFieldsList(cloud2);

        if( str.find("rgb") != std::string::npos ) {
            has_rgb = true;
		}
        if( str.find("normal") != std::string::npos ) {
            has_normal = true;
		}

        if( has_rgb && has_normal ) {
			pcl::fromPCLPointCloud2(cloud2, cloud_rgb_normal);
			pcl::io::pointCloudTovtkPolyData(cloud_rgb_normal, f_output);
		} else if( has_rgb ) {
			pcl::fromPCLPointCloud2(cloud2, cloud_rgb);
			pcl::io::pointCloudTovtkPolyData(cloud_rgb, f_output);
		} else if( has_normal ) {
			pcl::fromPCLPointCloud2(cloud2, cloud_normal);
			pcl::io::pointCloudTovtkPolyData(cloud_normal, f_output);
		} else {
			pcl::fromPCLPointCloud2(cloud2, cloud_xyz);
			pcl::io::pointCloudTovtkPolyData(cloud_xyz, f_output);
		}
	}

    return 1;
}
