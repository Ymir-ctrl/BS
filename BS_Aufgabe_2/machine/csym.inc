%macro CSYM 1
%ifdef PREFIX
    _%1
%else
    %1
%endif
%endmacro
