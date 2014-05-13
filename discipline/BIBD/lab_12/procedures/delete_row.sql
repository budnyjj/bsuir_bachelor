-- usage example:
-- call delete_row(3);

delimiter endproc
create procedure delete_row(IN _id int)
begin
    delete from warehouse where id = _id;
end;
endproc
delimiter ;
