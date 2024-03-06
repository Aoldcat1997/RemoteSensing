//#include<gdal_priv.h>
//#include "ogrsf_frmts.h"
//#include <errno.h>
//#include<iostream>
//#include<gdal_alg.h>
//using namespace std;
//int main()
//{
//	GDALAllRegister();
//	//դ��·��
//	const char* raster_path = "E:\\gdal\\JL_41_.tif";
//	// ʸ��·��
//	string shp_path = "E:\\gdal\\JL_41_64_5.shp";
//	// ��ȡդ���ļ�
//	// ��GDALDatasetH��ǿ��תΪ GDALDataset
//	GDALDataset* Rasterdata = (GDALDataset*)GDALOpen(raster_path, GA_ReadOnly);
//	// �ж������Ƿ��ȡ�ɹ�
//	if (Rasterdata == NULL)
//	{
//		printf("Open failed.\n");
//		exit(1);
//	}
//	// ��ȡ����
//	GDALRasterBand* RatserBand = Rasterdata->GetRasterBand(1);
//	// �����ռ�ο�
//	OGRSpatialReference spatialReference;
//	spatialReference.importFromEPSG(4326);
//	// ͬGDALOpen������ʸ������ļ�
//	string driverName = "ESRI Shapefile";
//	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName(driverName.c_str());
//	if (driver == NULL)
//	{
//		cout << "Faild Getting Driver:" << driverName << endl;
//
//	}
//
//	GDALDataset* shpdata = driver->Create(shp_path.c_str(), 0, 0, 0, GDT_Unknown, NULL);
//	if (shpdata == NULL)
//	{
//		cout << "create dataset failed ��" << shp_path << endl;
//		return -1;
//	}
//
//	//
//	/*GDALDataset* shpdata = static_cast<GDALDataset*>(
//		GDALOpenEx(shp_path, GDAL_OF_VECTOR, NULL, NULL, NULL));*/
//	//�ж������Ƿ��ȡ�ɹ�
//	if (shpdata == NULL)
//	    {
//	        printf("Open failed.\n");
//	        exit(1);
//	    }
//	// ����ͼ�㣬�洢ʸ������դ��
//	OGRLayer* layer = shpdata->CreateLayer("polygon", &spatialReference, wkbPolygon, NULL);
//	if (layer == NULL)
//	{
//		cout << "Faild Create Layer" << endl;
//		return -1;
//	}
//	OGRFieldDefn fieldDef1("value", OFTInteger);
//	fieldDef1.SetWidth(100);
//	// �жϸ��ֶδ����ɹ�
//	if (layer->CreateField(&fieldDef1) != OGRERR_NONE)
//	{
//		cout << "�ֶδ����ɹ�" << endl;
//		return -1;
//	}
//	// ִ��ʸ����������GDALTermProgress��ʾʸ��������
//	if(GDALFPolygonize(RatserBand,NULL,layer,0, NULL, GDALTermProgress, NULL) != CE_None);
//	{
//		// ����ִ�гɹ����ر����ݼ��ͷ��ڴ�
//		GDALClose((GDALDatasetH)Rasterdata);
//		GDALClose((GDALDatasetH)shpdata);
//		// delete spatialReference;
//		/*spatialReference = NULL;*/
//		cout << "�����ɹ�" << endl;
//		return 0;
//	}
//	//�ͷ��ڴ�
//	GDALClose((GDALDatasetH)Rasterdata);
//	GDALClose((GDALDatasetH)shpdata);
//
//
//	return 0;
//}