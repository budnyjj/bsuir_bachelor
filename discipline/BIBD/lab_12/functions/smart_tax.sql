-- usage example
-- select @tax = smart_tax(1);

delimiter endfunc
create function smart_tax(_id int)
    returns float
begin
    declare result float;
    declare cost int;
    declare tax_percent int;
    
    select price*count from warehouse
        where id = _id into cost;  

    if cost < 100000 then
        set tax_percent = 10;
    elseif cost > 100000 and cost < 500000 then
        set tax_percent = 12;
    else
        set tax_percent = 14;
    end if;

    set result = cost * tax_percent / 100;
    return result;
end;
endfunc
delimiter ;