DROP TABLE IF EXISTS accounts;
CREATE TABLE accounts(
    uid int(11) primary key auto_increment,
    uname varchar(30) NOT NULL,
    passwd varchar(255) NOT NULL,
    rtime date NOT NULL
)

DROP TABLE IF EXISTS upinfo;
CREATE TABLE upinfo(
    upid int(11) primary key,
    upname varchar(64) NOT NULL,
    des varchar(512),
    wtime date NOT NULL
)

DROP TABLE IF EXISTS usrinfo;
CREATE TABLE usrinfo(
    uid int(11) primary key,
    des varchar(512),
    face varchar(128),
    foreign key(uid) references accounts(uid)
    on delete cascade
)

DROP TABLE IF EXISTS watch;
CREATE TABLE watch(
    uid int(11) primary key,
    upid int(11),
    uwtime date,
    foreign key(upid) references upinfo(upid)
    on delete cascade,
    foreign key(uid) references accounts(uid)
    on delete cascade
)

DROP TABLE IF EXISTS cards;
CREATE TABLE cards(
    upid int(11) primary key,
    title varchar(255) NOT NULL,
    content varchar(512) NOT NULL,
    ptime datetime NOT NULL,
    foreign key(upid) references upinfo(upid)
    on delete cascade
)