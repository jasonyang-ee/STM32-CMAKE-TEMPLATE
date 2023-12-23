# Flash to Target

We are using VS Code Task `Ctrl + Shift + P` -> Enter `Tasks: run task`. This will allow auto excution of custom terminal commands.

Setting keyboard short cut `Ctrl + T` for this is going to help you very much.

The configuration can be defined by creating file `.vscode/tasks.json`

> tasks.json

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "type": "shell",
      "label": "Windows: Flash Firmware",
      "command": "STM32_Programmer_CLI",
      "args": [
        "--connect",
        "port=swd",
        "--download",
        "${command:cmake.launchTargetPath}",
        "-rst",
        "-run"
      ],
      "options": {
        "cwd": "${workspaceFolder}"
      },
      "problemMatcher": []
    }
  ]
}
```
![task shortcut](img/task.png)

# Additional Task

More task setting can be found in this project folder `.vscode/` for device reset, Linux flash, and cmake build.
