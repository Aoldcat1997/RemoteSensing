//#include"gdal_priv.h"
//
////������
//int main(int argc, const char* argv[])
//{
//	// register all Driver
//	GDALAllRegister();
//	// ����ͼ���ʽ�ַ�
//	const char* pszFormat = "GTiff";
//	// ����ָ�룬���ڴ洢ͼ������
//	GDALDriver* poDriver;
//	char** paszMetadata;
//	// ����tiff����,���Ƴ�ʼ��
//	poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
//	if (poDriver == NULL)
//		return  -1;
//	//ָ�����·��
//	const char* pszDstFilename = "E:\\gdal\\test.tif";
//	GDALDataset* poDstDS ;
//	char** papszOptions = NULL;
//	//����������Ĵ���������������դ������
//	poDstDS = poDriver->Create(pszDstFilename, 512,512,1,GDT_Byte, papszOptions);
//	//����ͶӰ
//	OGRSpatialReference oSRS;
//	oSRS.importFromEPSG(4326);
//	//Ϊդ��ָ��ͶӰ
//	poDstDS->SetSpatialRef(&oSRS);
//	//�趨ͶӰ����
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
//	// ��ȡ��һ��������
//	poBand = poDstDS->GetRasterBand(1);
//	// ����������д��
//	poBand->RasterIO(GF_Write, 0, 0, 512, 512, adyRaster, 512, 512, GDT_Byte, 0, 0);
//
//	//�ر����ݼ�
//	GDALClose((GDALDatasetH)poDstDS);
//	printf("������ݴ���");
//	return 0;
//}