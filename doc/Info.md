# Information

## Naming Convention

The Palm Engine follows the [Hungarian Notation](https://en.wikipedia.org/wiki/Hungarian_notation) naming convention.

### Examples

#### Type prefix

| Type | Prefix | Example |
| ----- | ----- | ----- |
| Pointer | `p` | `pVariable` |
| Integer | `n` | `nNumber` |
| String | `s` | `sName` |
| DWORD | `dw` | `dwStyle` |
| Boolean | `b` | `bBusy` |
| null-terminated String | `sz` | `szLastName` |
| char | `ch` | `chName` |
| Word | `w` | `wNumber` |
| Array | `a` | `aCounter` |
| long | `l` | `lCount` |

#### Scopes prefix

| Scope | Prefix | Example |
| ----- | ----- | ----- |
| Member Variable | `m_` | `m_szVariable` |
| Parameter | `p_` | `p_nNumber` |
| Interface-Parameter | `i_` | `i_dwStyle` |
| Static Variable | `s_` | `s_nInstanceCount` |
| Global Variable | `g_` | `g_aCounter` |