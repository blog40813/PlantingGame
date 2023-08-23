# PlantingGame
<!-- ![game](game/image/game_status=1.png) -->
<img src = "game/image/game_status=1.png" width = 60% >

This is my Introduction to Programming I project

## Installation

Make sure that you already have `codeblocks`, or you can download it [here](https://www.codeblocks.org/)<br><br>

#### Clone this repository. <br><br>
```
git clone https://github.com/blog40813/PlantingGame.git
```

#### Setting<br>

* 基本上都已經設定好了，如果出錯，檢查 project 的 `Build options`
<img src ="game/data/illustrate/buildoption.png" width =300>

* 一開始先將`allegro/include`加入到complier的`search directories` 裡面
<img src ="game/data/illustrate/complier.png" width =300>

* 分別將`liballegro_monolith-debug.dll.a` 以及 `liballegro_monolith.dll.a` 加入到 `debug` 跟 `release` 的 `linker settings`
  ###### (這兩個檔案會在allegro/lib裡面)

<img src ="game/data/illustrate/debug.png" width =40%>  <img src ="game/data/illustrate/release.png" width =40%>

## Start playing 
`W` `A` `S` `D`：控制游標位置/角色移動<br>
`J`： 種植/商店購買<br>
`K`： 殺死蟲蟲<br>
`L`： 收割作物 (各階段作物皆會消失) <br>
`H`： 變更種植作物 <br>
`P`： 進入商店<br>
`ESC`： 離開<br>
`ENTER`： 確認<br>


