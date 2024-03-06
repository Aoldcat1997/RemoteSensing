//#include <iostream>
//#include <gdal_priv.h>
//#include <ogrsf_frmts.h>
//
//int main() {
//    // 注册GDAL和OGR驱动
//    GDALAllRegister();
//    OGRRegisterAll();
//
//    // 打开栅格数据集
//    GDALDataset* rasterDataset = (GDALDataset*)GDALOpen("input_raster.tif", GA_ReadOnly);
//    if (rasterDataset == NULL) {
//        std::cerr << "Error: Failed to open raster dataset." << std::endl;
//        return 1;
//    }
//
//    // 创建矢量数据源
//    OGRSFDriver* driver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("ESRI Shapefile");
//    if (driver == NULL) {
//        std::cerr << "Error: Failed to create vector data source." << std::endl;
//        GDALClose(rasterDataset);
//        return 1;
//    }
//
//    // 打开或创建矢量文件
//    const char* vectorFileName = "output_vector.shp";
//    OGRDataSource* vectorDataSource = driver->CreateDataSource(vectorFileName, NULL);
//    if (vectorDataSource == NULL) {
//        std::cerr << "Error: Failed to create vector data source." << std::endl;
//        GDALClose(rasterDataset);
//        return 1;
//    }
//
//    // 从栅格数据集创建矢量图层
//    OGRLayer* vectorLayer = vectorDataSource->CreateLayer("output_layer", NULL, wkbPolygon, NULL);
//    if (vectorLayer == NULL) {
//        std::cerr << "Error: Failed to create vector layer." << std::endl;
//        GDALClose(rasterDataset);
//        OGRDataSource::DestroyDataSource(vectorDataSource);
//        return 1;
//    }
//
//    // 从栅格数据集创建矢量要素
//    GDALRasterBand* rasterBand = rasterDataset->GetRasterBand(1);
//    GDALPolygonize(rasterBand, NULL, vectorLayer, 0, NULL, NULL);
//
//    // 释放资源
//    GDALClose(rasterDataset);
//    OGRDataSource::DestroyDataSource(vectorDataSource);
//
//    std::cout << "Raster to Vector conversion completed." << std::endl;
//    return 0;
//}
