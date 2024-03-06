//#include<gdal_priv.h>
//#include "ogrsf_frmts.h"
//#include <errno.h>
//#include<iostream>
//#include<gdal_alg.h>
//using namespace std;
//int main()
//{
//	GDALAllRegister();
//	//栅格路径
//	const char* raster_path = "E:\\gdal\\JL_41_.tif";
//	// 矢量路径
//	string shp_path = "E:\\gdal\\JL_41_64_5.shp";
//	// 读取栅格文件
//	// 将GDALDatasetH类强制转为 GDALDataset
//	GDALDataset* Rasterdata = (GDALDataset*)GDALOpen(raster_path, GA_ReadOnly);
//	// 判断数据是否读取成功
//	if (Rasterdata == NULL)
//	{
//		printf("Open failed.\n");
//		exit(1);
//	}
//	// 获取波段
//	GDALRasterBand* RatserBand = Rasterdata->GetRasterBand(1);
//	// 创建空间参考
//	OGRSpatialReference spatialReference;
//	spatialReference.importFromEPSG(4326);
//	// 同GDALOpen，创建矢量输出文件
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
//		cout << "create dataset failed ：" << shp_path << endl;
//		return -1;
//	}
//
//	//
//	/*GDALDataset* shpdata = static_cast<GDALDataset*>(
//		GDALOpenEx(shp_path, GDAL_OF_VECTOR, NULL, NULL, NULL));*/
//	//判定数据是否读取成功
//	if (shpdata == NULL)
//	    {
//	        printf("Open failed.\n");
//	        exit(1);
//	    }
//	// 创建图层，存储矢量化的栅格
//	OGRLayer* layer = shpdata->CreateLayer("polygon", &spatialReference, wkbPolygon, NULL);
//	if (layer == NULL)
//	{
//		cout << "Faild Create Layer" << endl;
//		return -1;
//	}
//	OGRFieldDefn fieldDef1("value", OFTInteger);
//	fieldDef1.SetWidth(100);
//	// 判断该字段创建成功
//	if (layer->CreateField(&fieldDef1) != OGRERR_NONE)
//	{
//		cout << "字段创建成功" << endl;
//		return -1;
//	}
//	// 执行矢量化函数，GDALTermProgress显示矢量化进程
//	if(GDALFPolygonize(RatserBand,NULL,layer,0, NULL, GDALTermProgress, NULL) != CE_None);
//	{
//		// 函数执行成功，关闭数据集释放内存
//		GDALClose((GDALDatasetH)Rasterdata);
//		GDALClose((GDALDatasetH)shpdata);
//		// delete spatialReference;
//		/*spatialReference = NULL;*/
//		cout << "创建成功" << endl;
//		return 0;
//	}
//	//释放内存
//	GDALClose((GDALDatasetH)Rasterdata);
//	GDALClose((GDALDatasetH)shpdata);
//
//
//	return 0;
//}