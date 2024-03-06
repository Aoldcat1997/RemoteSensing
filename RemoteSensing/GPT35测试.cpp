//#include <iostream>
//#include <gdal_priv.h>
//#include <ogrsf_frmts.h>
//
//int main() {
//    // ע��GDAL��OGR����
//    GDALAllRegister();
//    OGRRegisterAll();
//
//    // ��դ�����ݼ�
//    GDALDataset* rasterDataset = (GDALDataset*)GDALOpen("input_raster.tif", GA_ReadOnly);
//    if (rasterDataset == NULL) {
//        std::cerr << "Error: Failed to open raster dataset." << std::endl;
//        return 1;
//    }
//
//    // ����ʸ������Դ
//    OGRSFDriver* driver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName("ESRI Shapefile");
//    if (driver == NULL) {
//        std::cerr << "Error: Failed to create vector data source." << std::endl;
//        GDALClose(rasterDataset);
//        return 1;
//    }
//
//    // �򿪻򴴽�ʸ���ļ�
//    const char* vectorFileName = "output_vector.shp";
//    OGRDataSource* vectorDataSource = driver->CreateDataSource(vectorFileName, NULL);
//    if (vectorDataSource == NULL) {
//        std::cerr << "Error: Failed to create vector data source." << std::endl;
//        GDALClose(rasterDataset);
//        return 1;
//    }
//
//    // ��դ�����ݼ�����ʸ��ͼ��
//    OGRLayer* vectorLayer = vectorDataSource->CreateLayer("output_layer", NULL, wkbPolygon, NULL);
//    if (vectorLayer == NULL) {
//        std::cerr << "Error: Failed to create vector layer." << std::endl;
//        GDALClose(rasterDataset);
//        OGRDataSource::DestroyDataSource(vectorDataSource);
//        return 1;
//    }
//
//    // ��դ�����ݼ�����ʸ��Ҫ��
//    GDALRasterBand* rasterBand = rasterDataset->GetRasterBand(1);
//    GDALPolygonize(rasterBand, NULL, vectorLayer, 0, NULL, NULL);
//
//    // �ͷ���Դ
//    GDALClose(rasterDataset);
//    OGRDataSource::DestroyDataSource(vectorDataSource);
//
//    std::cout << "Raster to Vector conversion completed." << std::endl;
//    return 0;
//}
