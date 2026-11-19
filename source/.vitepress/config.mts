import { defineConfig } from "vitepress"
export default defineConfig({
  srcExclude: ["public/**"],
  ignoreDeadLinks: [/^\/downloads\//, /^\/licenses\//, /^\/thanks\//],
  "lang": "zh-CN",
  "title": "Lyra Player 开发者文档",
  "description": "Lyra Player 插件 SDK、接口和开发指南",
  "base": "/LyraPlayer-docs-site/",
  "cleanUrls": true,
  "themeConfig": {
    "logo": "/logo.svg",
    "siteTitle": "Lyra Player",
    "nav": [
      {
        "text": "指南",
        "link": "/guide/start"
      },
      {
        "text": "插件",
        "link": "/plugins/first-plugin"
      },
      {
        "text": "配置",
        "link": "/config/reference/"
      },
      {
        "text": "SDK",
        "link": "/reference/abi"
      },
      {
        "text": "Agent / MCP",
        "link": "/plugins/agents"
      }
    ],
    "sidebar": [
      {
        "text": "开始",
        "items": [
          {
            "text": "阅读路线",
            "link": "/guide/start"
          },
          {
            "text": "SDK 版本与兼容性",
            "link": "/reference/snapshot"
          },
          {
            "text": "能力边界",
            "link": "/reference/limits"
          }
        ]
      },
      {
        "text": "开发插件",
        "items": [
          {
            "text": "准备环境",
            "link": "/developers/build"
          },
          {
            "text": "Agent / MCP",
            "link": "/plugins/agents"
          },
          {
            "text": "扩展模型",
            "link": "/plugins/extensions"
          },
          {
            "text": "第一个插件",
            "link": "/plugins/first-plugin"
          },
          {
            "text": "生命周期与所有权",
            "link": "/plugins/lifecycle"
          },
          {
            "text": "接口查询",
            "link": "/plugins/interfaces"
          },
          {
            "text": "服务与默认组件",
            "link": "/plugins/service-context"
          },
          {
            "text": "剪贴板消息接口",
            "link": "/plugins/clipboard"
          },
          {
            "text": "系统网页接口",
            "link": "/plugins/links"
          },
          {
            "text": "媒体数据插件",
            "link": "/plugins/media"
          },
          {
            "text": "Host 与 Scene",
            "link": "/plugins/host"
          },
          {
            "text": "样式与字体",
            "link": "/plugins/styles"
          },
          {
            "text": "参数 schema",
            "link": "/plugins/config-schema"
          },
          {
            "text": "播放规则",
            "link": "/plugins/rules"
          },
          {
            "text": "播放提供者",
            "link": "/plugins/playback"
          },
          {
            "text": "目录、歌词与分类",
            "link": "/plugins/data"
          },
          {
            "text": "Android 平台契约",
            "link": "/plugins/android"
          },
          {
            "text": "Android IDL 9",
            "link": "/reference/android-platform"
          },
          {
            "text": "包与元数据",
            "link": "/plugins/manifest"
          },
          {
            "text": "发布与镜像",
            "link": "/plugins/publishing"
          },
          {
            "text": "安全与信任",
            "link": "/plugins/security"
          },
          {
            "text": "测试与验收",
            "link": "/developers/testing"
          },
          {
            "text": "排错",
            "link": "/plugins/troubleshooting"
          },
          {
            "text": "设置页与消息端点",
            "link": "/plugins/messages"
          },
          {
            "text": "歌词格式与返回键",
            "link": "/plugins/presentation"
          }
        ]
      },
      {
        "text": "配置",
        "items": [
          {
            "text": "入门与文件位置",
            "link": "/config/getting-started"
          },
          {
            "text": "支持的语法",
            "link": "/config/syntax"
          },
          {
            "text": "校验规则",
            "link": "/config/validation"
          },
          {
            "text": "常用配方",
            "link": "/config/recipes"
          },
          {
            "text": "插件源",
            "link": "/config/repositories"
          },
          {
            "text": "个人曲库分类",
            "link": "/config/classification"
          },
          {
            "text": "迁移与排错",
            "link": "/config/troubleshooting"
          },
          {
            "text": "全部默认配置",
            "link": "/config/reference/"
          }
        ]
      },
      {
        "text": "参考与维护",
        "items": [
          {
            "text": "公开 C SDK",
            "link": "/reference/abi"
          },
          {
            "text": "服务目录",
            "link": "/reference/services"
          },
          {
            "text": "播放协议与时间",
            "link": "/reference/playback"
          },
          {
            "text": "文档与 SDK 版本",
            "link": "/developers/docs"
          }
        ]
      }
    ],
    "outline": {
      "level": [
        2,
        3
      ],
      "label": "本页目录"
    },
    "search": {
      "provider": "local",
      "options": {
        "translations": {
          "button": { "buttonText": "搜索文档", "buttonAriaLabel": "搜索文档" },
          "modal": {
            "displayDetails": "显示详情",
            "resetButtonTitle": "清空搜索",
            "backButtonTitle": "返回",
            "noResultsText": "没有匹配结果",
            "footer": { "selectText": "打开", "navigateText": "切换", "closeText": "关闭" }
          }
        }
      }
    },
    "darkModeSwitchLabel": "主题",
    "sidebarMenuLabel": "目录",
    "returnToTopLabel": "返回顶部",
    "docFooter": {
      "prev": "上一篇",
      "next": "下一篇"
    }
  },
  "head": [
    [
      "link",
      {
        "rel": "icon",
        "type": "image/svg+xml",
        "href": "/LyraPlayer-docs-site/logo.svg"
      }
    ],
    [
      "link",
      {
        "rel": "stylesheet",
        "href": "/LyraPlayer-docs-site/vp-icons.css"
      }
    ]
  ]
})
