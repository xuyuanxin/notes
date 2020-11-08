

http://www.cnblogs.com/dkblog/archive/2011/08/26/2155018.html  python ����־loggingģ��ѧϰ

Python Howto ֮ logging ģ��

 http://python.jobbole.com/82221/  Python Howto ֮ logging ģ��

 ������Դ�ڶ�py2.7.9 docs��howto-logging���ּ�֮Դ�������⡣�ٷ��ĵ��������£����� |
 �������ص�pdf�汾��Ӧ����һ�µģ�https://docs.python.org/2/howto/logging.html
                                                                                     |
 ���ǲ������ĵ�����ǳ����Ľ���˳����Ϊ����ô�㶫���������С��롱���������ʹ��      |
 loggingģ���¼��־�漰�ĸ���Ҫ�࣬ʹ�ùٷ��ĵ��еĸ�����Ϊ���ʣ�
 logger�ṩ��Ӧ�ó������ֱ��ʹ�õĽӿڣ�
 handler��(logger������)��־��¼���͵����ʵ�Ŀ�������
 filter�ṩ��ϸ���豸���������������־��¼��
 formatter������־��¼�����������ʽ��

 дlog��һ��˳��Ϊ��
 һ������logger��
  ���ǲ�Ҫͨ��logging.Logger��ֱ��ʵ�����õ�logger��������Ҫͨ��
  logging.getLogger(��name��)
  ������logger����
                                                                                     |
  ����˵���ǲ���ʵ��Logger��ʵ���������������ڴ�����ͬһ��name�õ�����ͬһ��logger�� |
  ������ģ��֮����Թ�ͬʹ��ͬһ��logger��getLogger���������Ľ�����������ڲ�ʹ��    |
  loggerDict�ֵ���ά�������Ա�֤��ͬ��������Ϊkey��õ�ͬһ��logger�������ǿ���ͨ��|
  ʵ������֤һ�£�

  #test_logger1.py
  #coding:utf-8

  import logging
  print logging.getLogger("mydear")    
  import test_logger2
  test_logger2.run()           #�����ļ�2�еĺ�������֤����ģ�鹲ͬ����������

  #test_logger2.py
  #coding:utf-8

  import logging
  def run():
      print logging.getLogger("mydear")

  �����
  <logging.Logger object at 0x00000000020ECF28>
  <logging.Logger object at 0x00000000020ECF28>
                                                                                     |
  ������������ļ���ͨ����mydear������getLogger���Ա�֤�õ���logger������ͬһ�������ֱ�|
  ����Logger���ʵ�������ܱ�֤������logger֮��Ϳ����������logger������������־�� |
  ��setLevel���󶨿�����addHandler����ӹ�����addFilter�ȡ�������ɺ󣬾Ϳ��Ե���    |
  logger�ķ���д��־�ˣ�����5����־�����Ӧ��5����־��¼�������ֱ�Ϊlogger.debug��   |
  logger.info��logger.warning��logger.error��logger.critical��

 ��������Logger�������־����
  logger.setLevel(logging.DEBUG)  #DEBUG���ϵ���־����ᱻ��logger����
                                                                                     |
 ��������handler����
  handler����log�ַ���ĳ��Ŀ����������ڶ������õ�Handler��log�ַ�����ͬ��Ŀ�ĵأ� |
  ���ǿ���̨�������ļ�������ĳ����ʽ��stream������socket�ȡ�һ��logger���԰󶨶��   |
  handler�����磬һ����־����ͬʱ���������̨���ļ��С�

  ��FileHandler��StreamHandlerΪ����
  logfile= logging.FileHandler(��./log.txt��)#����һ��handler�����ڽ���־������ļ���
  console = logging.StreamHandler()        #������һ��handler������־������

  handler����Ҳ��Ҫ������־��������һ��logger���԰������handler������ÿ��handler��|
  ����־�������б�Ҫ�ġ���ͨ�׵Ļ��������磬������Ҫ����debug���ϼ������Ϣ����������|
  ��logger����־����ΪDEBUG��Ȼ���������error���ϵ���־���������̨����DEBUG���ϵ�|
  ��Ϣ������ļ��У����ַ�������Ҫ����Handler�����ơ�

  logfile.setLevel(logging.DEBUG)
  console.setLevel(logging.ERROR)

  ���˶�handler����������־�����⣬������ָ��formatter������־�������ʽ����handler��|
  ��������־��ʽ��˵���˿��Խ�һ����¼�Բ�ͬ�ĸ�ʽ���������̨���ļ�������Ŀ�ĵء�

  formatter = logging.Formatter(��%(asctime)s �C %(name)s �C %(levelname)s �C %(message)s��)
  logfile.setFormatter(formatter) #����handler����־�����ʽ

  formatter����ʱʹ�õĹؼ��֣��������б����ʽչ�֣��ⲻ���ص㡣

 �ġ���handler��logger��
  ����handlers��logger�Ѿ�׼�����ˣ��������Ǿͽ�handlers�󶨵�logger�ϣ�һ��logger�� |
  ����԰󶨶��handler��

  logger.addHandler(logfile)  #logger��ͨ��getLogger�õ���Logger����
  logger.addHandler(console)

 �塢ʹ��logger����д��־
  logger.debug(��some debug message.��)
  logger.info(��some info message.��)
                                                                                     |
  ����ȥ���м䲽��(����handler��������־�������������ʽ��)����������Logger��һ����|
  �������ֱ�ӵ���д��־�Ľӿڼ��ɣ��Ժ���Щ��־��������ǰ�����������

  �غ����ö����ݰ�������򵥵İ�.

  ����Ĵ��룬����򵥵ġ�����logging֮��ͽ�����д��־������

  #coding:utf-8

  import logging
  logging.debug("debug mes")
  logging.info("info mes")
  logging.warning("warn mes")

  ����̨������£�
  WARNING:root:warn mes

  �ף�������ʲô�����Ϊʲôֻ�����warning��handler��logger��formatterȥ�Ķ��ˣ�
  -_-!˵�õ���򵥵��أ�Ϊ�����Լ������ã��Ҿ����ܰ������ͳɡ���򵥵ġ���
                                                                                     |
 ֪ʶ��1��logger����ڼ̳й�ϵ
  loggerͨ�������������̳й�ϵ�����һ��logger�������ǡ�mydest������һ��logger�������� |
  ��mydest.dest1�壨getLogger(��mydest.dest1��)��,��ô�ͳƺ�����ǰ�ߵ���logger����̳�ǰ |
  �ߵ����á�����Ĵ���û��ָ��logger��ֱ�ӵ���logging.debug�ȷ���ʱ����ʹ������logger|
  ��������RootLogger��������Ĵ������н�����Բ²������RootLogger���õ���־������   |
  logging.WARN�����Ŀ�ĵ��Ǳ�׼����

 ֪ʶ��2��basicConfig������������RootLogger
  basicConfig��������������RootLogger��rootLogger������Logger������Logger����������һ|
  ��Logger��̳и�Logger�����á��������basicConfigԴ�뿴���������������ؼ��ֲ�������|
  ��Ϊ��

  filename��ִ��ʹ�ø��ļ���ΪrootLogger����FileHandler��������StreamHandler
  filemode��ָ���ļ��򿪷�ʽ��Ĭ���ǡ�a��
  stream��ָ��һ��������ʼ��StreamHandler���˲������ܺ�filename���棬���ͬʱ�ṩ����|
           ������������stream����������
  format��ΪrootLogger��handlerָ�������ʽ
  datefmt��ָ�����������ʱ���ʽ
  level������rootLogger����־����

  ʹ��������
  logging.basicConfig(
                     filename = './log.txt',
                     filemode = 'a',
                     #stream = sys.stdout,
                     format = '%(levelname)s:%(message)s',
                     datefmt = '%m/%d/%Y %I:%M:%S',
                     level = logging.DEBUG
                      )

 ֪ʶ��3 ͨ��ʾ����ϸ����Logger���õļ̳й�ϵ
  ����׼���¼̳�������log2�̳���log1��logger�����ƿ������⣬Ҫע�⡮.����ʾ�ļ̳й�ϵ��

  #coding:utf-8

  import logging
  log1 = logging.getLogger("mydear")
  log1.setLevel(logging.WARNING)
  log1.addHandler(StreamHandler())
  log2 = logging.getLogger("mydear.app")
  log2.error("display")
  log2.info("not display")

  level�ļ̳�                                                                        
  ԭ����loggerд��־ʱ������ʹ�ñ��������˵�level�����û�����ã���������ϼ���    |
  logger��ѯ��ֱ����ѯ��Ϊֹ����˵�����ǣ�ʹ��rootLogger��Ĭ����־����           |
  logging.WARNING��

  handler�ļ̳�
  ԭ���Ƚ���־���󴫵ݸ���logger������handler����������Ϻ��������logger��    |
  propagate����û������Ϊ0������־�������ϴ��ݸ���һ����Logger���ø�logger������   |
  handler������Ϻ��������propagateҲû������Ϊ0����������ϲ㴫�ݣ��Դ����ơ�����|
  ��״̬��Ҫô����һ��Logger������propagate��������Ϊ��0��Ҫôһֱ����ֱ��rootLogger |
  ������ϡ�

  ������ʵ������Ļ����ϣ����������һ����룬����
  #coding:utf-8

  import logging
  log1 = logging.getLogger("mydear")
  log1.setLevel(logging.WARNING)
  log1.addHandler(StreamHandler())
  log2 = logging.getLogger("mydear.app")
  log2.error("display")
  log2.info("not display")
  print log2.handlers      #��ӡlog2�󶨵�handler

  ������£�
  display
  []
                                                                                     |
  ˵�õļ̳У�������logger��Ȼû�а󶨸����handler��what��s wrong? �����������      |
  handler��Դ���룬���������ˡ��������ɣ��ⲻ��������(��)�̳У�ֻ�ǡ���Ϊ�ϵļ̳С�:

  def callHandlers(self, record):
      """
      Pass a record to all relevant handlers.
  
      Loop through all handlers for this logger and its parents in the
      logger hierarchy. If no handler was found, output a one-off error
      message to sys.stderr. Stop searching up the hierarchy whenever a
      logger with the "propagate" attribute set to zero is found - that
      will be the last logger whose handlers are called.
      """
      c = self
      found = 0
      while c:
          for hdlr in c.handlers:         #���ȱ�����logger������handler
              found = found + 1
              if record.levelno >= hdlr.level:
                  hdlr.handle(record)
          if not c.propagate:             #���logger��propagate��������Ϊ0��ֹͣ
              c = None    #break out 
          else:                           #����ʹ��ֱ�Ӹ�logger
              c = c.parent
      ...

  ���򵥵�����ǣ��������ô���̨���߼����������Ƕ�һ��Ҳ���кô��ġ�
                                                                                     |
 ���棬���ǽ�һЩ����Ĳ��Ǻ���Ҫ�Ķ�������һ�£���ƪ�ͽ����ˡ�                      |
 1.����LogLevel��ȫ�ֱ�������������ʽ��ʾ��Ҳ���Ե��ǲ��Ƽ��Զ�����־���������Ҫ��|
 level����Ϊ�û����ã����ȡlevel�ͼ��level��һ������ǣ�

  #����loglevel�����û����õ�level����
  numeric_level = getattr(logging, loglevel.upper(), None)
  if not isinstance(numeric_level, int):
      raise ValueError('Invalid log level: %s' % loglevel)
  logging.basicConfig(level=numeric_level, ...)

 2.format��ʽ�����ڴ���formatter���󣬻���basicConfig�У��Ͳ�������
  %(name)s            Name of the logger (logging channel)
  %(levelno)s         Numeric logging level for the message (DEBUG, INFO,
  WARNING, ERROR, CRITICAL)
  %(levelname)s       Text logging level for the message (��DEBUG��, ��INFO��,
  ��WARNING��, ��ERROR��, ��CRITICAL��)
  %(pathname)s        Full pathname of the source file where the logging
  call was issued (if available)
  %(filename)s        Filename portion of pathname
  %(module)s          Module (name portion of filename)
  %(lineno)d          Source line number where the logging call was issued
  (if available)
  %(funcName)s        Function name
  %(created)f         Time when the LogRecord was created (time.time()
  return value)
  %(asctime)s         Textual time when the LogRecord was created
  %(msecs)d           Millisecond portion of the creation time
  %(relativeCreated)d Time in milliseconds when the LogRecord was created,
  relative to the time the logging module was loaded
  (typically at application startup time)
  %(thread)d          Thread ID (if available)
  %(threadName)s      Thread name (if available)
  %(process)d         Process ID (if available)
  %(message)s         The result of record.getMessage(), computed just as
  the record is emitted

 3.д��־�ӿ�
  logging.warn(��%s am a hero��, ��I��)   #1 %��ʽ�Բ�����ʽ�ṩʵ��
  logging.warn(��%s am a hero�� % (��I��,)) #2 ֱ���ṩ�ַ�����Ҳ����ʹ��format��template
  logging.warn(��%(name)s am a hero��, {��name��:��I��})  #�ؼ��ֲ���
  logging.warn(��%(name)s am a hero�� % {��name��:��I��}) #��������Ҳ����
  logging.warn(��%(name)s am a hero, %(value)s�� % {��name��:��I��, ��value��:'Yes��}) #ԭ��%Ҳ�ܽ����ؼ��ֲ�������һ������Ԫ��

  ����ؼ��ֺ�λ�ò��������أ�%Ӧ�ò�����ʲô��Ϊ�ˣ���ǿҲ����������

  logging.warn(��%(name)s am a hero, %()s�� % {��name��:��I�� ,��: ��Yes��})#Ҳ���ֵ��ʽ����ԭ��
                                                                                     |
 4.����logging��
  �����Ѿ������������handler���󶨵�logger�������Ҫһ����΢�Ӵ����־ϵͳ����������|
  �����ǻ�ʹ�úö��addHandler��SetFormatter֮��ģ��й����ˡ��Һã�loggingģ���ṩ��|
  ���ֶ������÷���������Ҫд�ڶ���룬ֱ�Ӵ����ýṹ�л�Ϥ���ǵ�������ͼ

  ��ʽһ��ʹ�������ļ�
  import logging
  import logging.config
  logging.config.fileConfig('logging.conf')
  # create logger
  logger = logging.getLogger('simpleExample')
  # 'application' code
  logger.debug('debug message')
  logger.info('info message')
  logger.warn('warn message')
  logger.error('error message')
  logger.critical('critical message')

  #�����ļ�logging.conf������
  [loggers]
  keys=root,simpleExample
  [handlers]
  keys=consoleHandler
  [formatters]
  keys=simpleFormatter
  [logger_root]
  level=DEBUG
  handlers=consoleHandler
  [logger_simpleExample]
  level=DEBUG
  handlers=consoleHandler
  qualname=simpleExample
  propagate=0
  [handler_consoleHandler]
  class=StreamHandler
  level=DEBUG
  formatter=simpleFormatter
  args=(sys.stdout,)
  [formatter_simpleFormatter]
  format=%(asctime)s - %(name)s - %(levelname)s - %(message)s
  datefmt=

  ��ʽ����ʹ���ֵ�

  �����python2.7.9 Library�ĵ�������:

  https://docs.python.org/2/library/logging.config.html?highlight=dictconfig#configuration-dictionary-schema
                                                                                     |
 5.�ڶ��handler���㲻ͬ�������Ҫ
  StreamHandler��FileHandler��NullHandler��RotatingFileHandler��                     |
  TimedRotatingFileHandler��SocketHandler��DatagramHandler��SMTPHandler��            |
  SysLogHandler��NTEventLogHandler��MemoryHandler��HTTPHandler��WatchedFileHandler��

  ����ǰ������loggingģ���и�������������logging.handlersģ���и�����
  
  

