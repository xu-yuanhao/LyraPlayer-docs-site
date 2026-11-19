# Android 平台 IDL 9

检查 Activity 的 `lyraPlatformVersion()I` 返回 9 后，按下表解析 JNI 方法。

[下载 IDL](/downloads/sdk/android-platform-v9.json) · [线程与资源](/plugins/android)

## Activity

| ID | 方法 | JNI descriptor |
| --- | --- | --- |
| 0 | `lyraPlatformVersion` | `()I` |
| 1 | `syncMotionArtwork` | `(JLjava/lang/String;ZZZZLjava/lang/String;IFFFFFZ)V` |
| 2 | `clearMotionArtwork` | `()V` |
| 3 | `setStatusBarHidden` | `(Z)V` |
| 4 | `setNavigationBarHidden` | `(Z)V` |
| 5 | `syncLibraryIncremental` | `()I` |
| 6 | `choosePlugin` | `(Ljava/lang/String;)V` |
| 7 | `takePluginFd` | `()I` |
| 8 | `chooseScanFolder` | `(Ljava/lang/String;Z)V` |
| 9 | `takeScanFolder` | `()Ljava/lang/String;` |
| 10 | `applyScanStrategy` | `(Ljava/lang/String;Ljava/lang/String;Z)J` |
| 11 | `refreshAboutAvatar` | `(Ljava/lang/String;I)V` |
| 12 | `getAppVersion` | `()Ljava/lang/String;` |
| 13 | `requestVerifiedResource` | `(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;II)I` |
| 14 | `pollVerifiedResource` | `(I)Ljava/lang/String;` |
| 15 | `cancelVerifiedResource` | `(I)V` |
| 16 | `readSiblingText` | `(JLjava/lang/String;I)Ljava/lang/String;` |
| 17 | `requestMediaResource` | `(Ljava/lang/String;Ljava/lang/String;IIIII)I` |
| 18 | `pollMediaResource` | `(I)Ljava/lang/String;` |
| 19 | `cancelMediaResource` | `(I)V` |
| 20 | `setQueryText` | `(Ljava/lang/String;)V` |
| 21 | `requestAudioPermission` | `()V` |
| 22 | `requestNamedPermission` | `(Ljava/lang/String;)I` |
| 23 | `showQuery` | `(Z)V` |
| 24 | `acquireSurface` | `(Ljava/lang/String;II)I` |
| 25 | `startLibraryScan` | `()V` |
| 26 | `setBackIntercept` | `(Z)V` |
| 27 | `setStatusContrast` | `(Z)V` |
| 28 | `refreshInsets` | `()V` |
| 29 | `loadCover` | `(JJI)Landroid/graphics/Bitmap;` |
| 30 | `loadCoverBytes` | `([BI)Landroid/graphics/Bitmap;` |
| 31 | `loadAssetBitmap` | `(Ljava/lang/String;I)Landroid/graphics/Bitmap;` |
| 32 | `openTrack` | `(J)V` |
| 33 | `openReadFd` | `(J)I` |
| 34 | `noteSearch` | `()V` |
| 35 | `updateSessionMetadata` | `(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;J)V` |
| 36 | `onPlaybackEnded` | `()V` |
| 37 | `listPlugins` | `(Z)[Ljava/lang/String;` |
| 38 | `isSystemDarkTheme` | `()Z` |
| 39 | `applyLyraTheme` | `(Z)V` |
| 40 | `extractMotionArtwork` | `(III)I` |
| 41 | `normalizeMotionArtwork` | `([B)I` |
| 42 | `requestAudioDeletion` | `(J)I` |
| 43 | `takeDeletedAudio` | `()J` |
| 44 | `motionSurface` | `(Landroid/view/Surface;)V` |
| 45 | `haptic` | `(I)V` |
| 46 | `chooseDocument` | `(Ljava/lang/String;Ljava/lang/String;)V` |
| 47 | `takeDocumentFd` | `()I` |

## 常量

| 名称 | 值 |
| --- | --- |
| `MotionStateCount` | 18 |
| `MotionAspect` | 16 |
| `MotionOpacity` | 17 |
| `MotionUpdated` | 2 |
