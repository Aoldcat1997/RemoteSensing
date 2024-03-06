//#include <gdal_priv.h>
//#include <ogrsf_frmts.h>
//#include <iostream>
//#include<gdal_alg.h>
//int main() {
//    GDALAllRegister();
//
//    // ��դ������
//    GDALDataset* pDataset = static_cast<GDALDataset*>(GDALOpen("E:\\gdal\\JL_41_.tif", GA_ReadOnly));
//    if (pDataset == nullptr) {
//        std::cerr << "GDALOpen failed - " << CPLGetLastErrorMsg() << std::endl;
//        return 1;
//    }
//
//    // �������ʸ���ļ�
//    const char* pszDriverName = "ESRI Shapefile";
//    GDALDriver* pDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
//    if (pDriver == nullptr) {
//        std::cerr << "GDAL Driver not found." << std::endl;
//        return 1;
//    }
//    GDALDataset* pOutDataset = pDriver->Create("E:\\gdal\\JL_41_64_55.shp", 0, 0, 0, GDT_Unknown, nullptr);
//    if (pOutDataset == nullptr) {
//        std::cerr << "GDAL Dataset creation failed." << std::endl;
//        return 1;
//    }
//
//    OGRLayer* pLayer = pOutDataset->CreateLayer("layer", nullptr, wkbPolygon, nullptr);
//    if (pLayer == nullptr) {
//        std::cerr << "Layer creation failed." << std::endl;
//        return 1;
//    }
//
//    // ʹ��GDALPolygonize����դ��ʸ����ת��
//    GDALRasterBand* pBand = pDataset->GetRasterBand(1); // �ٶ����Ǵ�����ǵ�һ������
//    CPLErr err = GDALPolygonize(pBand, nullptr, pLayer, -1, nullptr, nullptr, nullptr);
//    if (err != CE_None) {
//        std::cerr << "Polygonization failed - " << CPLGetLastErrorMsg() << std::endl;
//        return 1;
//    }
//
//    // ������Դ
//    GDALClose(pDataset);
//    GDALClose(pOutDataset);
//
//    return 0;
//}
