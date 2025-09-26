# universalproto

## config.json

Defines specific devices, system modes, error codes, etc.

Also included: overall configuration of sensors and their channels. This should probably
be a separate configuration independent of the spec since different setups have different
channel configs (?)

## types.json

Defines composite types to be used as payload specifications in packets.json.

## packets.json

Defines packets.

## rfc/todo

- Make device mnemonics 2 letters for uniformity?
- Keep types.json where composite types can be defined to keep packets.json a bit more polished.
- Change "id" to "tag" or something? Since currently IP + id can be interpreted as the actual "id". So id = IP + tag?
- Move error packet "id"s (StateTransitionError) to a dedicated region?
- Hotswapped AC RBV???
- How should channel mappings be configured?
