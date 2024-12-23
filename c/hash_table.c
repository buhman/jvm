#include <stdint.h>

static uint32_t fnv_1(const uint8_t * buf, int length)
{
  const uint32_t fnv_offset_basis = 0x811c9dc5;
  const uint32_t fnv_prime = 0x01000193;

  uint32_t hash = fnv_offset_basis;

  for (int i = 0; i < length; i++) {
    hash = hash * fnv_prime;
    hash = hash ^ buf[i];
  }

  return hash;
}

struct hash_table_entry {
  const uint8_t * key;
  int key_length;
  void * value;
  struct hash_table_entry * next;
};

void hash_table_init(int hash_table_length,
                     struct hash_table_entry * entry,
                     struct hash_table_entry * overflow)
{
  for (int i = 0; i < hash_table_length; i++) {
    entry[i].key = nullptr;
    entry[i].next = nullptr;
    overflow[i].key = nullptr;
    overflow[i].next = nullptr;
  }
}

static int max = 0;

void hash_table_add(int hash_table_length,
                    struct hash_table_entry * entry,
                    struct hash_table_entry * overflow,
                    int * overflow_length,
                    const uint8_t * key,
                    int key_length,
                    void * value)
{
  uint32_t hash = fnv_1(key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e->next != nullptr) {
    e = e->next;
  }

  int i = 0;
  if (e->key != nullptr) {
    if ((++i) > max) max = i;

    // allocate e from overflow
    e->next = &overflow[(*overflow_length)++];
    e = e->next;
  }

  e->key = key;
  e->key_length = key_length;
  e->value = value;
}

static inline bool key_equal(const uint8_t * a, const uint8_t * b, int length)
{
  for (int i = 0; i < length; i++) {
    if (a[i] != b[i])
      return false;
  }
  return true;
}


#include <stdio.h>

struct hash_table_entry * hash_table_find(int hash_table_length,
                                          struct hash_table_entry * entry,
                                          struct hash_table_entry * overflow,
                                          const uint8_t * key,
                                          int key_length)
{
  uint32_t hash = fnv_1(key, key_length) & (hash_table_length - 1);
  struct hash_table_entry * e = &entry[hash];

  while (e->key != nullptr) {
    if (e->key_length == key_length && key_equal(e->key, key, key_length)) {
      return e;
    }
    printf("collision %s %s\n", (char *)e->key, (char *)key);
    e = e->next;
  }
  return nullptr;
}

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

static const char * names[] = {
  "java/beans/Introspector.java",
  "java/beans/PropertyDescriptor.java",
  "java/beans/PropertyVetoException.java",
  "java/beans/BeanInfo.java",
  "java/beans/Customizer.java",
  "java/beans/FeatureDescriptor.java",
  "java/beans/BeanDescriptor.java",
  "java/beans/Beans.java",
  "java/beans/AppletInitializer.java",
  "java/beans/Expression.java",
  "java/beans/MethodDescriptor.java",
  "java/beans/PropertyChangeSupport.java",
  "java/beans/PropertyChangeEvent.java",
  "java/beans/DesignMode.java",
  "java/beans/EventSetDescriptor.java",
  "java/beans/IndexedPropertyDescriptor.java",
  "java/beans/VetoableChangeListener.java",
  "java/beans/ConstructorProperties.java",
  "java/beans/IndexedPropertyChangeEvent.java",
  "java/beans/PropertyEditorManager.java",
  "java/beans/IntrospectionException.java",
  "java/beans/PropertyChangeListener.java",
  "java/beans/XMLEncoder.java",
  "java/beans/Visibility.java",
  "java/beans/VetoableChangeSupport.java",
  "java/beans/ParameterDescriptor.java",
  "java/beans/XMLDecoder.java",
  "java/beans/PropertyChangeListenerProxy.java",
  "java/beans/ExceptionListener.java",
  "java/beans/VetoableChangeListenerProxy.java",
  "java/beans/DefaultPersistenceDelegate.java",
  "java/beans/EventHandler.java",
  "java/beans/Statement.java",
  "java/beans/PropertyEditor.java",
  "java/beans/PropertyEditorSupport.java",
  "java/beans/SimpleBeanInfo.java",
  "java/beans/PersistenceDelegate.java",
  "java/beans/Encoder.java",
  "java/beans/beancontext/BeanContextChildSupport.java",
  "java/beans/beancontext/BeanContextServicesSupport.java",
  "java/beans/beancontext/BeanContextServiceRevokedEvent.java",
  "java/beans/beancontext/BeanContextSupport.java",
  "java/beans/beancontext/BeanContextServiceAvailableEvent.java",
  "java/beans/beancontext/BeanContextServiceProvider.java",
  "java/beans/beancontext/BeanContextProxy.java",
  "java/beans/beancontext/BeanContextServiceProviderBeanInfo.java",
  "java/beans/beancontext/BeanContextContainerProxy.java",
  "java/beans/beancontext/BeanContextMembershipListener.java",
  "java/beans/beancontext/BeanContextServices.java",
  "java/beans/beancontext/BeanContextServiceRevokedListener.java",
  "java/beans/beancontext/BeanContext.java",
  "java/beans/beancontext/BeanContextChildComponentProxy.java",
  "java/beans/beancontext/BeanContextMembershipEvent.java",
  "java/beans/beancontext/BeanContextEvent.java",
  "java/beans/beancontext/BeanContextServicesListener.java",
  "java/beans/beancontext/BeanContextChild.java",
  "java/net/ContentHandler.java",
  "java/net/URL.java",
  "java/net/FileNameMap.java",
  "java/net/SocketOptions.java",
  "java/net/DatagramSocketImplFactory.java",
  "java/net/UnknownServiceException.java",
  "java/net/SocketPermission.java",
  "java/net/NoRouteToHostException.java",
  "java/net/NetPermission.java",
  "java/net/URI.java",
  "java/net/DatagramSocket.java",
  "java/net/DatagramPacket.java",
  "java/net/BindException.java",
  "java/net/SocketTimeoutException.java",
  "java/net/ProxySelector.java",
  "java/net/MalformedURLException.java",
  "java/net/URLStreamHandlerFactory.java",
  "java/net/InetAddress.java",
  "java/net/PortUnreachableException.java",
  "java/net/DatagramSocketImpl.java",
  "java/net/UnknownHostException.java",
  "java/net/ProtocolException.java",
  "java/net/Proxy.java",
  "java/net/PasswordAuthentication.java",
  "java/net/SocketAddress.java",
  "java/net/MulticastSocket.java",
  "java/net/ServerSocket.java",
  "java/net/JarURLConnection.java",
  "java/net/Authenticator.java",
  "java/net/URLStreamHandler.java",
  "java/net/ConnectException.java",
  "java/net/NetworkInterface.java",
  "java/net/URLConnection.java",
  "java/net/URLEncoder.java",
  "java/net/InetSocketAddress.java",
  "java/net/URISyntaxException.java",
  "java/net/ResolverCache.java",
  "java/net/Socket.java",
  "java/net/Inet4Address.java",
  "java/net/SocketException.java",
  "java/net/SocketImplFactory.java",
  "java/net/ContentHandlerFactory.java",
  "java/net/HttpURLConnection.java",
  "java/net/URLDecoder.java",
  "java/net/SocketImpl.java",
  "java/net/URLClassLoader.java",
  "java/net/Inet6Address.java",
  "java/net/MimeTypeMapper.java",
  "java/math/MathContext.java",
  "java/math/BigInteger.java",
  "java/math/BigDecimal.java",
  "java/math/RoundingMode.java",
  "java/io/FileWriter.java",
  "java/io/FilePermission.java",
  "java/io/OutputStreamWriter.java",
  "java/io/ObjectInput.java",
  "java/io/BufferedOutputStream.java",
  "java/io/IOError.java",
  "java/io/LineNumberReader.java",
  "java/io/StringReader.java",
  "java/io/BufferedInputStream.java",
  "java/io/CharArrayWriter.java",
  "java/io/InputStreamReader.java",
  "java/io/Console.java",
  "java/io/FileOutputStream.java",
  "java/io/StringBufferInputStream.java",
  "java/io/DataOutput.java",
  "java/io/UTFDataFormatException.java",
  "java/io/ObjectStreamConstants.java",
  "java/io/ObjectStreamException.java",
  "java/io/BufferedReader.java",
  "java/io/FilenameFilter.java",
};
const int names_length = (sizeof (names)) / (sizeof (names[0]));

int main()
{
  int hash_table_length = 512;
  struct hash_table_entry entry[hash_table_length];
  struct hash_table_entry overflow[hash_table_length];
  int overflow_length = 0;

  hash_table_init(hash_table_length,
                  entry,
                  overflow);

  for (int i = 0; i < names_length; i++) {
    hash_table_add(hash_table_length,
                   entry,
                   overflow,
                   &overflow_length,
                   (const uint8_t *)names[i],
                   strlen(names[i]),
                   (void *)(ptrdiff_t)(i * 2));
  }

  printf("overflow_length %d %d\n", overflow_length, max);

  for (int j = 0; j < names_length; j++) {
    struct hash_table_entry * e = hash_table_find(hash_table_length,
                                                  entry,
                                                  overflow,
                                                  (const uint8_t *)names[j],
                                                  strlen(names[j]));
    assert(e != nullptr);
    printf("%s %d\n", e->key, (int)e->value);
  }
}
