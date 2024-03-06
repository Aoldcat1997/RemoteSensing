//#include "gdalwarper.h"
//#include"gdal_priv.h"
//// 影像投影变换
//int main()
//{
//    // 数据集结构体指针
//    GDALDatasetH  hSrcDS, hDstDS;
//
//    // Open input and output files.
//    // 注册驱动器
//    GDALAllRegister();
//    // 创建输入输出数据引用
//    hSrcDS = GDALOpen("E:\\gdal\\test.tif", GA_ReadOnly);
//    hDstDS = GDALOpen("E:\\gdal\\out.tif", GA_Update);
//
//    // Setup warp options.
//    // 设置变化选项，释放函数：GDALDestroyWarpOptions
//    GDALWarpOptions* psWarpOptions = GDALCreateWarpOptions();
//    // 源影像
//    psWarpOptions->hSrcDS = hSrcDS;
//    // 目标影像
//    psWarpOptions->hDstDS = hDstDS;
//    // 波段数量
//    psWarpOptions->nBandCount = 1;
//    // the band number for source image to process band number 
//    psWarpOptions->panSrcBands =
//        (int*)CPLMalloc(sizeof(int) * psWarpOptions->nBandCount);
//    psWarpOptions->panSrcBands[0] = 1;
//    // the band number for destination image to process band number 
//    psWarpOptions->panDstBands =
//        (int*)CPLMalloc(sizeof(int) * psWarpOptions->nBandCount);
//    psWarpOptions->panDstBands[0] = 1;
//    // 处理进程报告函数
//    psWarpOptions->pfnProgress = GDALTermProgress;
//
//    // Establish reprojection transformer.
//    // 设置投影转换参数：GDALCreateGenImgProjTransformer（img1,cood_ref2,img2,cood_ref2）
//    // 释放函数 GDALDestroyGenImgProjTransformer
//    psWarpOptions->pTransformerArg =
//        GDALCreateGenImgProjTransformer(hSrcDS,
//            GDALGetProjectionRef(hSrcDS),
//            hDstDS,
//            GDALGetProjectionRef(hDstDS),
//            FALSE, 0.0, 1);
//    psWarpOptions->pfnTransformer = GDALGenImgProjTransform;
//
//    // Initialize and execute the warp operation.
//    GDALWarpOperation oOperation;
//    // 执行变换操作
//    // 参数初始化
//    oOperation.Initialize(psWarpOptions);
//    // 设置偏移量与栅格像元大小
//    printf("x:%d,y%d", GDALGetRasterXSize(hDstDS),
//        GDALGetRasterYSize(hDstDS));
//    printf("sizeof(int) * psWarpOptions->nBandCount) size:%zd:", sizeof(int) * psWarpOptions->nBandCount);
//    printf("。。。。\n");
//    // This method does a complete warp of the source image to 
//    // the destination image for the indicated region with the current warp options in effect.
//    oOperation.ChunkAndWarpImage(0, 0,
//        GDALGetRasterXSize(hDstDS),
//        GDALGetRasterYSize(hDstDS));
//    // 释放投影参数内存
//    GDALDestroyGenImgProjTransformer(psWarpOptions->pTransformerArg);
//    GDALDestroyWarpOptions(psWarpOptions);
//    // 关闭数据
//    GDALClose(hDstDS);
//    GDALClose(hSrcDS);
//    return 0;
//}