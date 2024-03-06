//#include"gdal_priv.h"
//
////主函数
//int main(int argc, const char* argv[])
//{
//	// register all Driver
//	GDALAllRegister();
//	// 定义图像格式字符
//	const char* pszFormat = "GTiff";
//	// 驱动指针，用于存储图像驱动
//	GDALDriver* poDriver;
//	char** paszMetadata;
//	// 创建tiff驱动,类似初始化
//	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
//	if (poDriver == NULL)
//		return  -1;
//	//指定输出路径
//	const char* pszDstFilename = "E:\\gdal\\test.tif";
//	GDALDataset* poDstDS ;
//	char** papszOptions = NULL;
//	//调用驱动类的创建函数，来生成栅格数据
//	poDstDS = poDriver->Create(pszDstFilename, 512,512,1,GDT_Byte, papszOptions);
//	//定义投影
//	OGRSpatialReference oSRS;
//	oSRS.importFromEPSG(4326);
//	//为栅格指定投影
//	poDstDS->SetSpatialRef(&oSRS);
//	//设定投影参数
//	double adfGeoTransform[6] = {122, 0.01, 0, 32, 0, -0.01};
//	poDstDS->SetGeoTransform(adfGeoTransform);
//
//	// 
//	GDALRasterBand* poBand;
//	GByte adyRaster[512 * 512];
//	
//	memset(adyRaster, 0, sizeof(GByte) * 512 * 512);
//	for (int i = 0; i < 256; i++)
//	{
//		for (int j = 0; j < 256; j++)
//		{
//			adyRaster[i * 512 + j] = GByte(rand() % 128);
//		}
//	}
//	for (int i = 256; i < 512; i++)
//	{
//		for (int j = 256; j < 512; j++)
//		{
//			adyRaster[i * 512 + j] = GByte(rand() % 128+128);
//		}
//	}
//	// 获取第一波段索引
//	poBand = poDstDS->GetRasterBand(1);
//	// 将波段数据写入
//	poBand->RasterIO(GF_Write, 0, 0, 512, 512, adyRaster, 512, 512, GDT_Byte, 0, 0);
//
//	//关闭数据集
//	GDALClose((GDALDatasetH)poDstDS);
//	printf("完成数据创建");
//	return 0;
//}