# 播放命令、快照与时间

此参考用于插件调用或实现播放能力，不公开宿主算法。通过 query\_interface 获取接口；snapshot 先设置 size，返回的是值。

## 快照标识

| 字段 | 单位/含义 |
| --- | --- |
| `track_id` | 媒体曲目 ID，不能当数组行 |
| `position_us` / `duration_us` | int64 微秒 |
| `sampled_ns` | 单调采样时间，纳秒 |
| `output_frame` | 音频输出帧，不是显示帧 |
| `generation` | 曲目/提供者时代标识，拒绝旧结果 |
| `revision` | 时间重定位变化标识 |
| `seek_serial` / `landed_seek` | seek 请求与落地序列 |
| `feature_epoch` | 音频特征连续性标识 |
| `sample_rate` | 音频采样率 |
| energy/bass/mid/high/accent | 同音频时间轴的特征值 |

flags 组合：ACTIVE=1、PAUSED=2、CLOCK\_READY=4、SEEKING=8、FEATURES\_READY=16。只在对应 READY 标志存在时消费有效时钟或特征；active 不等于正在播放，paused 可以同时存在。

不要用 now\_ns 的经过时间自行累加音乐进度。动画可用绘制时钟，歌词/频谱与进度使用播放快照。seek 预览是局部 UI 状态，不是已经听到的音频位置。

## 客户端命令

| kind | 用途 | 关键参数 |
| --- | --- | --- |
| TOGGLE | 播放/暂停切换 | 无 |
| NEXT / PREVIOUS | 当前规则下下一首/上一首 | 无 |
| SELECT | 选择目录曲目 | index = 目录行 |
| QUEUE\_SELECT | 选择真实队列项 | index = 队列行 |
| MODE | 修改播放模式 | index = 模式 ID |
| PAUSE / RESUME | 明确暂停/恢复 | 无 |
| SEEK | 请求跳转 | position\_us，seek\_origin |

其余 OPEN/STOP/PRIME/CLEAR\_PRIME/REAP/REMEMBER 属于提供者/生命周期操作。普通 UI 插件不要随意重新 OPEN 以实现暂停或每次 seek，这会改变 generation、fd 和资源所有权。

command 返回 0 执行、1 接受但延后、负数拒绝。帧内提交后不保证同帧 position 已改变，不能重复发命令“催进度”。

## 调用片段

```c
LyraPlaybackSnapshotV3 state = {0};
state.size = sizeof(state);
if (playback->snapshot(playback->user, &state) == 0) {
    int playing = (state.flags & LYRA_PLAYBACK_ACTIVE) &&
                  !(state.flags & LYRA_PLAYBACK_PAUSED);
    /* 根据 playing 绘制，不创建另一套音乐进度 Timer。 */
    (void)playing;
}

LyraPlaybackCommandV3 command = {0};
command.size = sizeof(command);
command.kind = LYRA_PLAYBACK_QUEUE_SELECT;
command.index = desired_queue_row;
int accepted = playback->command(playback->user, &command);
if (accepted >= 0) host->request_frame(host->user);
```

`desired_queue_row` 须是当前目录及队列版本中的有效行。

## 队列

queue 输出目录索引数组、容量和当前队列行。返回总数可能用于探测容量，先分配后读取，并检查当前 revision/曲目变化；不要把输出行直接写进 track\_id。

音频提供者的事件与退出协议见[提供者教程](/plugins/playback)；歌词文本时间见[数据接口](/plugins/data)。
