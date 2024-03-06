//#include <gdal_priv.h>
//#include <ogrsf_frmts.h>
//#include <iostream>
//#include<gdal_alg.h>
//int main() {
//    GDALAllRegister();
//
//    // 打开栅格数据
//    GDALDataset* pDataset = static_cast<GDALDataset*>(GDALOpen("E:\\gdal\\JL_41_.tif", GA_ReadOnly));
//    if (pDataset == nullptr) {
//        std::cerr << "GDALOpen failed - " << CPLGetLastErrorMsg() << std::endl;
//        return 1;
//    }
//
//    // 创建输出矢量文件
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
//    // 使用GDALPolygonize进行栅格到矢量的转换
//    GDALRasterBand* pBand = pDataset->GetRasterBand(1); // 假定我们处理的是第一个波段
//    CPLErr err = GDALPolygonize(pBand, nullptr, pLayer, -1, nullptr, nullptr, nullptr);
//    if (err != CE_None) {
//        std::cerr << "Polygonization failed - " << CPLGetLastErrorMsg() << std::endl;
//        return 1;
//    }
//
//    // 清理资源
//    GDALClose(pDataset);
//    GDALClose(pOutDataset);
//
//    return 0;
//}
