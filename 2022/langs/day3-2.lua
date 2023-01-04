#!/usr/bin/env lua
function part2()
  local res = 0
  while true do
    line1, line2, line3 = io.stdin:read(), io.stdin:read(), io.stdin:read()
    if line1 == nil then break end
    
    local a, b, c = {}, {}, {}
    for ch in line1:gmatch"." do a[ch] = true end
    for ch in line2:gmatch"." do b[ch] = true end
    for ch in line3:gmatch"." do c[ch] = true end
    
    for ch,_ in pairs(a) do
      if b[ch] and c[ch] then
        if string.upper(ch) == ch then
          res = res + 27 + (string.byte(ch) - string.byte('A'))
        else
          res = res + 1 + (string.byte(ch) - string.byte('a'))
        end
        break
      end
    end
  end
  print("Part 2: ", res)
end

part2()
