-- usage example
-- set @surn = surname_verification(0); select @surn;

delimiter endfunc
create function surname_verification(
    _code int)
    returns varchar(25)
begin
    declare result varchar(25);
    declare _surname varchar(25);
    select supplier_surname from products
        where code = _code into _surname;
    select _surname
        regexp '([eo]v$)' into result;
    return result;
end;
endfunc
delimiter ;
