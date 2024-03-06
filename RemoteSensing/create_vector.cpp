//#include<iostream>
//#include<string>
//#include<random>
//using namespace std;
//#include "ogrsf_frmts.h"
//
//int main()
//{
//	GDALAllRegister();
//	// 创建驱动
//	string driverName = "ESRI Shapefile";
//	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName(driverName.c_str());
//	if (driver == NULL)
//	{
//		cout << "Faild Getting Driver:" << driverName << endl;
//
//	}
//	string dataPath = "E:\\gdal\\point_out.shp";
//	GDALDataset* dataset = driver->Create(dataPath.c_str(), 0, 0, 0, GDT_Unknown, NULL);
//	if (dataset == NULL)
//	{
//		cout << "create dataset failed ：" << dataPath << endl;
//		return -1;
//	}
//	// 创建空间参考
//	OGRSpatialReference spatialReference;
//	spatialReference.importFromEPSG(4326);
//	// 创建图层
//	OGRLayer* layer = dataset->CreateLayer("school", &spatialReference, wkbPoint, NULL);
//	if (layer == NULL)
//	{
//		cout << "Faild Create Layer" << endl;
//		return -1;
//	}
//	OGRFieldDefn fieldDef1("name",OFTString);
//	fieldDef1.SetWidth(100);
//	if (layer->CreateField(&fieldDef1) != OGRERR_NONE)
//	{
//		cout << "Faild Create Field" << endl;
//		return -1;
//	}
//
//	OGRFieldDefn fieldDef2("type", OFTInteger);
//	fieldDef2.SetWidth(100);
//	if (layer->CreateField(&fieldDef2) != OGRERR_NONE)
//	{
//		cout << "Faild Create Field" << endl;
//		return -1;
//	}
//	OGRFieldDefn fieldDef3("area", OFTReal);
//	fieldDef3.SetWidth(100);
//	if (layer->CreateField(&fieldDef3) != OGRERR_NONE)
//	{
//		cout << "Faild Create Field" << endl;
//		return -1;
//	}
//	//完成数据创建，关闭图层、释放内存输出数据。
//	for (int i = 1; i < 100; i++)
//	{
//		string name = "schoole" + to_string(i);
//		int type = rand() % 3;
//		double area = rand() % 100 / 100;
//		OGRFeature* feature;
//		feature = OGRFeature::CreateFeature(layer->GetLayerDefn());
//		feature->SetField("name", name.c_str());
//		feature->SetField("Type", type);
//		feature->SetField("Area", area);
//
//		OGRPoint pt;
//		pt.setX(120.0 + rand() % 10 / 100);
//		pt.setY(120.0 + rand() % 10 / 100);
//		feature->SetGeometry(&pt);
//
//		if (layer->CreateFeature(feature) != OGRERR_NONE)
//		{
//			cout << "Faild Creating Feature:" << i << endl;
//			return -1;
//		}
//		OGRFeature::DestroyFeature(feature);
//
//	}
//	GDALClose(dataset);
//
//}