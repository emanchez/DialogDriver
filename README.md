# DialogDriver

Reads branching dialog from an XML file and runs it as a text-adventure style conversation in the
console. Written in C++ with [pugixml](https://pugixml.org/) (bundled, MIT) for parsing.

Demonstration video: https://youtu.be/IVzD2m7mbbY

Written in January 2019 as a personal project and not maintained since.

## How it works

Dialog lives in XML. An `npc` contains `event`s, and each event is a tree of `dialog` nodes linked
by `goto` ids (see [`first.xml`](DialogDriverProject/first.xml)):

```xml
<npc name="villager001">
  <event name="test">
    <dialog type="tree" id="2.1">
      <text>What brings ye to these parts?</text>
      <option id="1" goto="3.1">I am a mercenary seeking a contract.</option>
      <option id="2" goto="3.2">I am a merchant with some goods to trade!</option>
    </dialog>
    <dialog type="end" id="4.2">
      <text>Good luck, traveler!</text>
    </dialog>
  </event>
</npc>
```

- `type="tree"` nodes show their text and numbered options; picking an option jumps to its `goto` node.
- `type="end"` nodes show their text and finish the conversation.

The `DialogDriver` class ([`DialogDriver.h`](DialogDriverProject/DialogDriver.h)) wraps this:
`load_xml` → `load_head` (pick the NPC) → `load_event` (pick the conversation, which loads node
`1.1`) → loop on `prompt_selection` / `load_next` until a node returns an end code.
[`Source.cpp`](DialogDriverProject/Source.cpp) is a sample program that does exactly that.

## Build

Windows, Visual Studio (the committed build logs use the v141 / VS 2017 toolset). Open
`DialogDriverProject/DialogDriverProject.vcxproj`, build, and run with `first.xml` next to the
executable.

## Known limitations

- Each loaded node is allocated with `new` and never freed.
- Non-numeric input at the prompt is not handled.
- Windows only (`system("PAUSE")`), no tests, and build output (`Debug/`, `x64/`) is committed.
